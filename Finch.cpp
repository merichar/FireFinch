#include "Finch.h"

/** Random finch stuff **/
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "hidapi.h"

/* Global Variables */
hid_device *finch_handle; // The handle to communicate with the Finch
char sendReportCounter = 0; // Used to match incoming and outgoing report in the finchRead function
int syncLock = 0; // Used to prevent the threads from both reading from Finch simultaneously
int wasTappedVal; // Holds whether the Finch has been tapped since the last read
int wasShakenVal; // Holds whether the Finch has been shaken since the last read



/*****Firefox Core Header********/
#include "mozilla-config.h"
// #include "nsStringAPI.h"

#include "nsIObserverService.h"

#include "nsIHttpProtocolHandler.h"
#include "nsIHttpChannel.h"
#include "nsITraceableChannel.h"
#include "nsIURI.h"
#include "nsIDOMWindow.h"

#include "prmem.h"

NS_IMPL_ISUPPORTS1(Finch, IFinch)

Finch::Finch()
{
  /* member initializers and constructor code */
    int success;
   
    pthread_t threadid;
    success = connect(); // connect Finch
    // If success, then spawn the keep alive thread
    if(success) {
        pthread_create(&threadid,
                       NULL,
                       keepAliveEntryPoint,  // entry-point-function
                       this);          // "this" pointer so we can reach the function we want
    }

}

Finch::~Finch()
{
  /* destructor code */
//     disConnect(); 

}


/* Finch hardware (non mozilla) code begins here */

/**
 * Connects to a Finch object. Called by the constructor. Left public for creative uses, but in general should not
 * be used independent of the constructor.
 * @return -1 if connection failed, 1 if connection succeeded.
 */
int Finch::connect() {
    // Associate the handle with the Finch's VID (0x2354) and PID (0x1111)
    finch_handle = hid_open(0x2354, 0x1111, NULL);
    if (!finch_handle) {
//      printf("Unable to connect to Finch, maybe it's not plugged in or another Finch program is already running?\n");
//      return -1;
    }  
    else {
        // Turn off the LED to indicate that the connection succeeded
        setLED(0,0,0);
        return 1;
    }  
}

/**
 * Tells Finch to go back to idle mode, then closes the connection
 * @return a positive number if resetting the Finch succeeded, -1 if it failed
 */
int Finch::disConnect() {
    unsigned char bufToWrite[9];
    int res;
   
    // send an 'R', which resets the Finch to idle mode
    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'R';

    res = finchWrite(bufToWrite);
    hid_close(finch_handle);
    return res;
}

/**
 * Not for use by user. The function called to keep the Finch from moving into idle mode while
 * a program is running.
 */
void Finch::keepAlive()
{
    while(1) {
        if(syncLock == 0) {
                counter(); // Note that calling this makes syncLock = 1, so at most this gets called every two seconds
        }
        else {
            syncLock = 0; // Reset syncLock
        }
        sleep(1);
    }
}


/**
 * Generic function to read data from the Finch.
 * @param bufToWrite 9-byte array to send to Finch to indicate what should be read.
 * @param bufRead 9-byte array containing raw returned value from Finch
 * @return -1 if read failed, 1 is read succeeded.
 */
int Finch::finchRead(unsigned char bufToWrite[], unsigned char bufRead[])
{
    int res; // Holds the result of the HIDAPI hid_write and hid_read commands
        unsigned char tempReportCounter=sendReportCounter;
    // Use the "sendReportCounter" to associate a specific command report with a resulting
    // read report.
    // If we're using the 'z' command (counter command), we don't need to do this since we're
    // only using it for the keepAlive thread.
    if(bufToWrite[1] != 'z') {
        bufToWrite[8] = sendReportCounter;
        sendReportCounter++;
    }
    syncLock = 1; // Prevent the other thread from calling a finchRead at the same time
   
    // Write a command report
    res = hid_write(finch_handle, bufToWrite, 9);
    if(res == -1) {
        printf("Error, failed to write a read command.");
        printf("Error is: %ls\n", hid_error(finch_handle));
        return -1;
    }
    else { 
        // Read the raw data using hid_read. If the returned report counter value does
        // not match our value, try again (this is for safety only, in practice, this loop
        // only runs once).
        do {
            res = hid_read(finch_handle, bufRead, 9);
            if(res == -1) {
                printf("Error, failed to read.");
                printf("Error is: %ls\n", hid_error(finch_handle));
                return -1;
            }
        }
        while((bufRead[7] != tempReportCounter)&& (bufToWrite[1] != 'z'));
        // If you got here, your read succeeded. Yeay!
        return 1;

    }
}


/**
 * Generic write-only method, used for set functions that don't expect returned data.
 * @param bufToWrite A 9 byte array containing the command report.
 * @return A positive number of the write succeeded, -1 if it failed.
 */
int Finch::finchWrite(unsigned char bufToWrite[])
{
    int returnVal = 0;
    // Make sure the keepAlive thread knows we're writing the Finch so it doesn't
    // try to execute a write at the same time.
    syncLock = 1;
    returnVal = hid_write(finch_handle, bufToWrite, 9);
    // printf("OMG PRINTF\n");
    return returnVal;
}


/**
 * Used by the keep alive method, left public for creative uses but not ordinarily used by the user.
 * This function reads the Finch's ping method, which simply returns the number of times the Finch has been
 * pinged (a number from 0 to 255, overflow returns the value to 0).
 * @return Number of times the counter method has been called, -1 if read failed.
 */
int Finch::counter()
{
  unsigned char bufToWrite[9];
  unsigned char bufRead[9];

  bufToWrite[0] = 0x0;
  bufToWrite[1] = 'z';     
  if(finchRead(bufToWrite, bufRead)==1) {
    return ((int)bufRead[0]);
  }  
  else {
    return -1;
  }
}

double* Finch::getAccelerations() {
    unsigned char bufToWrite[9]; // Holds the command report
    unsigned char bufRead[9]; // Holds the raw returned data
    double* accelerations = new double[3];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'A';
    if(finchRead(bufToWrite, bufRead)==1) {
        // Convert the raw accelerometer data to G-forces
        for(int i = 0; i < 3; i++)
        {
            if(bufRead[i+1] > 31) {
                accelerations[i] = (bufRead[i+1]-64)*1.5/32;
            }
            else {
                accelerations[i] = bufRead[i+1]*1.5/32;
            }
        }
        // Check if the latest read indicated the Finch was shaken or tapped.
        // If so, set the wasTapped and/or wasShaken flags.
        wasTappedVal = wasTappedVal || ((bufRead[4] & 0x20)>>5);
        wasShakenVal = wasShakenVal || ((bufRead[4] & 0x80)>>7);
        return accelerations;
    }
    else {
        return 0;
    }
}


/**
 * Sets the color and intensity of the beak LED. 
 * @param red Intensity of the red color element, range is 0 to 255
 * @param green Intensity of the green color element, range is 0 to 255
 * @param blue Intensity of the blue color element, range is 0 to 255
 * @return a positive number if the LED was set, -1 if the command failed.
 */
int Finch::setLED(int red, int green, int blue) {
    unsigned char bufToWrite[9];
    
    // Check to make sure that the values are in range
    if(red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0)
    {
        return -1;
    }
    else 
    {
        // Create command report, then write it to the Finch
        bufToWrite[0] = 0x0;
        bufToWrite[1] = 'O';
        bufToWrite[2] = (char)red;
        bufToWrite[3] = (char)green;
        bufToWrite[4] = (char)blue;
        return finchWrite(bufToWrite);
    }
	return 0;
}

int* Finch::getObstacleSensors() {
    unsigned char bufToWrite[9];
    unsigned char bufRead[9];
    int* obstacleSensors = new int[2];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'I';
    if(finchRead(bufToWrite, bufRead)==1) {
        obstacleSensors[0] = (int)bufRead[0];
        obstacleSensors[1] = (int)bufRead[1];
        return obstacleSensors;
    }
    else {
        return 0;
    }
}

int* Finch::getLightSensors() {
    unsigned char bufToWrite[9]; // Holds command report
    unsigned char bufRead[9]; // Holds raw returned data
    int* lightSensors = new int[2]; // Holds array to return

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'L';
    if(finchRead(bufToWrite, bufRead)==1) {
        lightSensors[0] = (int)bufRead[0]; // Convert values from char to int
        lightSensors[1] = (int)bufRead[1];
        return lightSensors;
    }
    else {
        return 0;
    }
}


/* Finch Hardware code ends here */



/* double getTemperature (); */
NS_IMETHODIMP Finch::GetTemperature(double *_retval NS_OUTPARAM)
{
    unsigned char bufToWrite[9]; // Holds the command report
    unsigned char bufRead[9]; // Holds the raw returned data
    double temperature; // Holds the final calculated temperature
    temperature = 42.69;
    // Create a command report that requests temperature data
    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'T';
    if(finchRead(bufToWrite, bufRead)==1) {
        temperature = (bufRead[0]-127)/2.4 + 25; // Convert raw temperature to Celcius
        *_retval =  temperature;
    }
    else {
        *_retval =  -1;
    }
   *_retval = temperature;
  return NS_OK;
}

/* long setLED (in long red, in long green, in long blue); */
NS_IMETHODIMP Finch::SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM)
{   
        unsigned char bufToWrite[9];
    
    // Check to make sure that the values are in range
    if(red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0)
    {   
    }   
    else 
    {   
        // Create command report, then write it to the Finch
        bufToWrite[0] = 0x0;
        bufToWrite[1] = 'O';
        bufToWrite[2] = (char)red;
        bufToWrite[3] = (char)green;
        bufToWrite[4] = (char)blue;
        *_retval= finchWrite(bufToWrite);
    }
    return NS_OK;
}

/* long setMotors (in long leftWheelSpeed, in long rightWheelSpeed); */
NS_IMETHODIMP Finch::SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM)
{   
    /**
 * Sets the speed of the left and right wheels.
 * @param leftWheelSpeed Power to the left wheel, range is -255 to 255
 * @param rightWheelSpeed Power to the right wheel, range is -255 to 255
 * @return a positive number if the motors were set, -1 if the command failed.
 */
    unsigned char bufToWrite[9];
   
    char leftDir = 0;
    char rightDir = 0;
    // If the numbers are negative, set the direction bit to 1, and make the negative speed positive
    if(leftWheelSpeed < 0) {
        leftWheelSpeed = -leftWheelSpeed;
        leftDir = 1;
    }
    if(rightWheelSpeed < 0) {
        rightWheelSpeed = -rightWheelSpeed;
        rightDir = 1;
    }
   
    // Check to make sure speeds are within the range
    if(leftWheelSpeed > 255 || rightWheelSpeed > 255) {
        return NS_OK;
    }
    else {
        // Create a command report to set the motor speeds.
        bufToWrite[0] = 0x0;
        bufToWrite[1] = 'M';
        bufToWrite[2] = leftDir;
        bufToWrite[3] = (char)leftWheelSpeed;
        bufToWrite[4] = rightDir;
        bufToWrite[5] = (char)rightWheelSpeed;
        // Write the report to Finch
        *_retval = finchWrite(bufToWrite);
	return NS_OK;
    }

    return NS_OK;
}

/* long setMotorsd (in long leftWheelSpeed, in long rightWheelSpeed, in long duration); */
NS_IMETHODIMP Finch::SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM)
{   
    unsigned char bufToWrite[9];
  
    char leftDir = 0;
    char rightDir = 0;
    // If the numbers are negative, set the direction bit to 1, and make the negative speed positive
    if(leftWheelSpeed < 0) {
        leftWheelSpeed = -leftWheelSpeed;
        leftDir = 1;
    }
    if(rightWheelSpeed < 0) {
        rightWheelSpeed = -rightWheelSpeed;
        rightDir = 1;
    }
  
    // Check to make sure speeds are within the range
    if(leftWheelSpeed > 255 || rightWheelSpeed > 255) {
        return NS_OK;
    }
    else {
        // Create a command report to set the motor speeds.
        bufToWrite[0] = 0x0;
        bufToWrite[1] = 'M';
        bufToWrite[2] = leftDir;
        bufToWrite[3] = (char)leftWheelSpeed;
        bufToWrite[4] = rightDir;
        bufToWrite[5] = (char)rightWheelSpeed;
        // Write the report to Finch
        *_retval = finchWrite(bufToWrite);
	 usleep(duration*1000);
	bufToWrite[0] = 0x0;
        bufToWrite[1] = 'M';
        bufToWrite[2] = leftDir;
        bufToWrite[3] = (char)0;
        bufToWrite[4] = rightDir;
        bufToWrite[5] = (char)0;

        return NS_OK;
    }

    return NS_OK;

}

/* long noteOn (in long frequency); */
NS_IMETHODIMP Finch::NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM)
{   
    unsigned char bufToWrite[9];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'B';
    bufToWrite[2] = 0xFF;
    bufToWrite[3] = 0xFF;
    bufToWrite[4] = (char)((frequency & 0x0000FFFF)>>8);
    bufToWrite[5] = (char)(frequency & 0x000000FF);

    *_retval= finchWrite(bufToWrite);
	return NS_OK;
}

/* long noteOnd (in long frequency, in long duration); */
NS_IMETHODIMP Finch::NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM)
{   

    unsigned char bufToWrite[9];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'B';
    bufToWrite[2] = 0xFF;
    bufToWrite[3] = 0xFF;
    bufToWrite[4] = (char)((frequency & 0x0000FFFF)>>8);
    bufToWrite[5] = (char)(frequency & 0x000000FF);

    *_retval = finchWrite(bufToWrite);
    usleep(duration*1000);
        bufToWrite[0] = 0x0;
    bufToWrite[1] = 'B';
    bufToWrite[2] = 0x0;
    bufToWrite[3] = 0x0;
    bufToWrite[4] = 0x0;
    bufToWrite[5] = 0x0;

    *_retval = finchWrite(bufToWrite);

    return NS_OK;
}

/* long noteOff (); */
NS_IMETHODIMP Finch::NoteOff(PRInt32 *_retval NS_OUTPARAM)
{   
    unsigned char bufToWrite[9];
    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'B';
    bufToWrite[2] = 0x0;
    bufToWrite[3] = 0x0;
    bufToWrite[4] = 0x0;
    bufToWrite[5] = 0x0;

    *_retval= finchWrite(bufToWrite);

    return NS_OK;
}

/* double getAccelerations (); */
NS_IMETHODIMP Finch::GetAccelerations(double *_retval NS_OUTPARAM)
{  
    #if 0 
    unsigned char bufToWrite[9]; // Holds the command report
    unsigned char bufRead[9]; // Holds the raw returned data
    double* accelerations = new double[3];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'A';
    if(finchRead(bufToWrite, bufRead)==1) {
        // Convert the raw accelerometer data to G-forces
        for(int i = 0; i < 3; i++)
        {
            if(bufRead[i+1] > 31) {
                accelerations[i] = (bufRead[i+1]-64)*1.5/32;
            }
            else {
                accelerations[i] = bufRead[i+1]*1.5/32;
            }
        }
        // Check if the latest read indicated the Finch was shaken or tapped.
        // If so, set the wasTapped and/or wasShaken flags.
        wasTappedVal = wasTappedVal || ((bufRead[4] & 0x20)>>5);
        wasShakenVal = wasShakenVal || ((bufRead[4] & 0x80)>>7);
        *_retval =  accelerations;
    }
    else {
        *_retval = 0;
    }
    #endif
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getLightSensors (); */
NS_IMETHODIMP Finch::GetLightSensors(PRInt32 *_retval NS_OUTPARAM)
{   
    #if 0 
    unsigned char bufToWrite[9]; // Holds command report
    unsigned char bufRead[9]; // Holds raw returned data
    int* lightSensors = new int[2]; // Holds array to return

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'L';
    if(finchRead(bufToWrite, bufRead)==1) {
        lightSensors[0] = (int)bufRead[0]; // Convert values from char to int
        lightSensors[1] = (int)bufRead[1];
        *_retval = lightSensors;
    }
    else {
        *_retval =  0;
    }
    #endif
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getObstacleSensors (); */
NS_IMETHODIMP Finch::GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM)
{
    #if 0
    unsigned char bufToWrite[9];
    unsigned char bufRead[9];
    int* obstacleSensors = new int[2];

    bufToWrite[0] = 0x0;
    bufToWrite[1] = 'I';
    if(finchRead(bufToWrite, bufRead)==1) {
        obstacleSensors[0] = (int)bufRead[0];
        obstacleSensors[1] = (int)bufRead[1];
        *_retval= obstacleSensors;
    }
    else {
        *_retval= 0;
    }
	#endif
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean wasTapped (); */
NS_IMETHODIMP Finch::WasTapped(PRBool *_retval NS_OUTPARAM)
{
    int toReturn;
    // We need to do at least one call to getAccelerations to get the current tapped state
    // We are also using this call to detect failure to read
    if(getAccelerations()==0) {
        *_retval= -1;
    }
    toReturn = wasTappedVal;
    wasTappedVal = 0;
    *_retval= toReturn;

    return NS_OK;
}

/* boolean wasShaken (); */
NS_IMETHODIMP Finch::WasShaken(PRBool *_retval NS_OUTPARAM)
{
    int toReturn;
    // We need to do at least one call to getAccelerations to get the current shaken state
    // We are also using this call to detect failure to read
    if(getAccelerations()==0) {
        *_retval= -1;
    }
    toReturn = wasShakenVal;
    wasShakenVal = 0;
    *_retval = toReturn;

    return NS_OK;
}

/* boolean isObstacleLeftSide (); */
NS_IMETHODIMP Finch::IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM)
{
    int* obstacles = getObstacleSensors();
    if(obstacles == 0) {
        *_retval= -1;
    }
    else {
        *_retval = obstacles[0];
    }

    return NS_OK;
}

/* boolean isObstacleRightSide (); */
NS_IMETHODIMP Finch::IsObstacleRightSide(PRBool *_retval NS_OUTPARAM)
{
    int* obstacles = getObstacleSensors();
    if(obstacles == 0) {
        *_retval= -1;
    }
    else {
        *_retval= obstacles[1];
    }

    return NS_OK;
}

/* long getLeftLightSensor (); */
NS_IMETHODIMP Finch::GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM)
{
    int* lightSensors = getLightSensors();
    if(lightSensors == 0) {
        *_retval= -1;
    }
    else {
        *_retval= lightSensors[0];
    }

    return NS_OK;
}

/* long getRightLightSensor (); */
NS_IMETHODIMP Finch::GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM)
{
    int* lightSensors = getLightSensors();
    if(lightSensors == 0) {
        *_retval= -1;
    }
    else {
        *_retval= lightSensors[1];
    }
	return NS_OK;
}

/* double getXAcceleration (); */
NS_IMETHODIMP Finch::GetXAcceleration(double *_retval NS_OUTPARAM)
{
    double* accelerations = getAccelerations();
    if(accelerations == 0) {
        *_retval= -2;
    }
    else {
        *_retval= accelerations[0];
    }

    return NS_OK;
}

/* double getYAcceleration (); */
NS_IMETHODIMP Finch::GetYAcceleration(double *_retval NS_OUTPARAM)
{
    double* accelerations = getAccelerations();
    if(accelerations == 0) {
        *_retval= -2;
    }
    else {
        *_retval= accelerations[1];
    }

    return NS_OK;
}

/* double getZAcceleration (); */
NS_IMETHODIMP Finch::GetZAcceleration(double *_retval NS_OUTPARAM)
{
    double* accelerations = getAccelerations();
    if(accelerations == 0) {
        *_retval= -2;
    }
    else {
        *_retval= accelerations[2];
    }

    return NS_OK;
}

/* boolean isBeakUp (); */
NS_IMETHODIMP Finch::IsBeakUp(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
     {
         if (accels[0] < -0.8 && accels[0] > -1.5 && accels[1] > -0.3 && accels[1] < 0.3 && accels[2] > -0.3 && accels[2] < 0.3)
            {
            *_retval= 1;
            }
         else {
             *_retval= 0;
         }
     }
  else {
     *_retval= -1;
  }
 return NS_OK;
}

/* boolean isBeakDown (); */
NS_IMETHODIMP Finch::IsBeakDown(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
  {
    if (accels[0] < 1.5 && accels[0] > 0.8 && accels[1] > -0.3 && accels[1] < 0.3 && accels[2] > -0.3 && accels[2] < 0.3)
    {
        *_retval= 1;
    }
    else
    {
        *_retval= 0;
    }
  }
  else {
    *_retval= -1;
  }
return NS_OK;
}

/* boolean isFinchLevel (); */
NS_IMETHODIMP Finch::IsFinchLevel(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
  {
        if (accels[0] > -0.5 && accels[0] < 0.5 && accels[1] > -0.5 && accels[1] < 0.5 && accels[2] > 0.65 && accels[2] < 1.5)
        {
            *_retval= 1;
        }
        else {
            *_retval= 0;
        }
  }
  else {
    *_retval= 0;
  }
  return NS_OK;
}

/* boolean isFinchUpsideDown (); */
NS_IMETHODIMP Finch::IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
  {
    if (accels[0] > -0.5 && accels[0] < 0.5 && accels[1] > -0.5 && accels[1] < 0.5 && accels[2] > -1.5 && accels[2] < -0.65)
    {
        *_retval= 1;
    }
    else {
        *_retval= 0;
    }
  }
  else {
    *_retval= -1;
  }

    return NS_OK;
}

/* boolean isRightWingDown (); */
NS_IMETHODIMP Finch::IsRightWingDown(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
  {
     if (accels[0] > -0.5 && accels[0] < 0.5 && accels[1] > -1.5 && accels[1] < -0.7 && accels[2] > -0.5 && accels[2] < 0.5)
     {
        *_retval= 1;
     }
     else {
         *_retval= 0;
     }
  }
  else {
     *_retval= -1;
  }

return NS_OK;
}

/* boolean isLeftWingDown (); */
NS_IMETHODIMP Finch::IsLeftWingDown(PRBool *_retval NS_OUTPARAM)
{
  double* accels = getAccelerations();
  if (accels != 0)
  {
    if (accels[0] > -0.5 && accels[0] < 0.5 && accels[1] > 0.7 && accels[1] < 1.5 && accels[2] > -0.5 && accels[2] < 0.5)
    {
        *_retval= 1;
    }
    else {
        *_retval= 0;
    }
  }
  else {
     *_retval= -1;
  }

return NS_OK;
}

