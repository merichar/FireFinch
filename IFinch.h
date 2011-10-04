/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IFinch.idl
 */

#ifndef __gen_IFinch_h__
#define __gen_IFinch_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IFinch */
#define IFINCH_IID_STR "c901edf0-ddb9-11e0-9572-0800200c9a66"

#define IFINCH_IID \
  {0xc901edf0, 0xddb9, 0x11e0, \
    { 0x95, 0x72, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFinch : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFINCH_IID)

  /* long setLED (in long red, in long green, in long blue); */
  NS_SCRIPTABLE NS_IMETHOD SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long setMotors (in long leftWheelSpeed, in long rightWheelSpeed); */
  NS_SCRIPTABLE NS_IMETHOD SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long setMotorsd (in long leftWheelSpeed, in long rightWheelSpeed, in long duration); */
  NS_SCRIPTABLE NS_IMETHOD SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long noteOn (in long frequency); */
  NS_SCRIPTABLE NS_IMETHOD NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long noteOnd (in long frequency, in long duration); */
  NS_SCRIPTABLE NS_IMETHOD NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long noteOff (); */
  NS_SCRIPTABLE NS_IMETHOD NoteOff(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* double getAccelerations (); */
  NS_SCRIPTABLE NS_IMETHOD GetAccelerations(double *_retval NS_OUTPARAM) = 0;

  /* long getLightSensors (); */
  NS_SCRIPTABLE NS_IMETHOD GetLightSensors(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long getObstacleSensors (); */
  NS_SCRIPTABLE NS_IMETHOD GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* boolean wasTapped (); */
  NS_SCRIPTABLE NS_IMETHOD WasTapped(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean wasShaken (); */
  NS_SCRIPTABLE NS_IMETHOD WasShaken(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isObstacleLeftSide (); */
  NS_SCRIPTABLE NS_IMETHOD IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isObstacleRightSide (); */
  NS_SCRIPTABLE NS_IMETHOD IsObstacleRightSide(PRBool *_retval NS_OUTPARAM) = 0;

  /* long getLeftLightSensor (); */
  NS_SCRIPTABLE NS_IMETHOD GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long getRightLightSensor (); */
  NS_SCRIPTABLE NS_IMETHOD GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* double getXAcceleration (); */
  NS_SCRIPTABLE NS_IMETHOD GetXAcceleration(double *_retval NS_OUTPARAM) = 0;

  /* double getYAcceleration (); */
  NS_SCRIPTABLE NS_IMETHOD GetYAcceleration(double *_retval NS_OUTPARAM) = 0;

  /* double getZAcceleration (); */
  NS_SCRIPTABLE NS_IMETHOD GetZAcceleration(double *_retval NS_OUTPARAM) = 0;

  /* boolean isBeakUp (); */
  NS_SCRIPTABLE NS_IMETHOD IsBeakUp(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isBeakDown (); */
  NS_SCRIPTABLE NS_IMETHOD IsBeakDown(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isFinchLevel (); */
  NS_SCRIPTABLE NS_IMETHOD IsFinchLevel(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isFinchUpsideDown (); */
  NS_SCRIPTABLE NS_IMETHOD IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isRightWingDown (); */
  NS_SCRIPTABLE NS_IMETHOD IsRightWingDown(PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean isLeftWingDown (); */
  NS_SCRIPTABLE NS_IMETHOD IsLeftWingDown(PRBool *_retval NS_OUTPARAM) = 0;

  /* double getTemperature (); */
  NS_SCRIPTABLE NS_IMETHOD GetTemperature(double *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFinch, IFINCH_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFINCH \
  NS_SCRIPTABLE NS_IMETHOD SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD NoteOff(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetAccelerations(double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetLightSensors(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD WasTapped(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD WasShaken(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleRightSide(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetXAcceleration(double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetYAcceleration(double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetZAcceleration(double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsBeakUp(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsBeakDown(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsFinchLevel(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsRightWingDown(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsLeftWingDown(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetTemperature(double *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFINCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM) { return _to SetLED(red, green, blue, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM) { return _to SetMotors(leftWheelSpeed, rightWheelSpeed, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) { return _to SetMotorsd(leftWheelSpeed, rightWheelSpeed, duration, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM) { return _to NoteOn(frequency, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) { return _to NoteOnd(frequency, duration, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOff(PRInt32 *_retval NS_OUTPARAM) { return _to NoteOff(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAccelerations(double *_retval NS_OUTPARAM) { return _to GetAccelerations(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLightSensors(PRInt32 *_retval NS_OUTPARAM) { return _to GetLightSensors(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM) { return _to GetObstacleSensors(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD WasTapped(PRBool *_retval NS_OUTPARAM) { return _to WasTapped(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD WasShaken(PRBool *_retval NS_OUTPARAM) { return _to WasShaken(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM) { return _to IsObstacleLeftSide(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleRightSide(PRBool *_retval NS_OUTPARAM) { return _to IsObstacleRightSide(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM) { return _to GetLeftLightSensor(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM) { return _to GetRightLightSensor(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetXAcceleration(double *_retval NS_OUTPARAM) { return _to GetXAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetYAcceleration(double *_retval NS_OUTPARAM) { return _to GetYAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetZAcceleration(double *_retval NS_OUTPARAM) { return _to GetZAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBeakUp(PRBool *_retval NS_OUTPARAM) { return _to IsBeakUp(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBeakDown(PRBool *_retval NS_OUTPARAM) { return _to IsBeakDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsFinchLevel(PRBool *_retval NS_OUTPARAM) { return _to IsFinchLevel(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM) { return _to IsFinchUpsideDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsRightWingDown(PRBool *_retval NS_OUTPARAM) { return _to IsRightWingDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsLeftWingDown(PRBool *_retval NS_OUTPARAM) { return _to IsLeftWingDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTemperature(double *_retval NS_OUTPARAM) { return _to GetTemperature(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFINCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLED(red, green, blue, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMotors(leftWheelSpeed, rightWheelSpeed, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMotorsd(leftWheelSpeed, rightWheelSpeed, duration, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->NoteOn(frequency, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->NoteOnd(frequency, duration, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD NoteOff(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->NoteOff(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAccelerations(double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccelerations(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLightSensors(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLightSensors(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetObstacleSensors(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD WasTapped(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->WasTapped(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD WasShaken(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->WasShaken(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsObstacleLeftSide(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsObstacleRightSide(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsObstacleRightSide(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLeftLightSensor(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRightLightSensor(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetXAcceleration(double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetXAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetYAcceleration(double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetYAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetZAcceleration(double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetZAcceleration(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBeakUp(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsBeakUp(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBeakDown(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsBeakDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsFinchLevel(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsFinchLevel(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsFinchUpsideDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsRightWingDown(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsRightWingDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsLeftWingDown(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsLeftWingDown(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTemperature(double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTemperature(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFinch
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFINCH

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFinch)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* long setLED (in long red, in long green, in long blue); */
NS_IMETHODIMP _MYCLASS_::SetLED(PRInt32 red, PRInt32 green, PRInt32 blue, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long setMotors (in long leftWheelSpeed, in long rightWheelSpeed); */
NS_IMETHODIMP _MYCLASS_::SetMotors(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long setMotorsd (in long leftWheelSpeed, in long rightWheelSpeed, in long duration); */
NS_IMETHODIMP _MYCLASS_::SetMotorsd(PRInt32 leftWheelSpeed, PRInt32 rightWheelSpeed, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long noteOn (in long frequency); */
NS_IMETHODIMP _MYCLASS_::NoteOn(PRInt32 frequency, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long noteOnd (in long frequency, in long duration); */
NS_IMETHODIMP _MYCLASS_::NoteOnd(PRInt32 frequency, PRInt32 duration, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long noteOff (); */
NS_IMETHODIMP _MYCLASS_::NoteOff(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double getAccelerations (); */
NS_IMETHODIMP _MYCLASS_::GetAccelerations(double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getLightSensors (); */
NS_IMETHODIMP _MYCLASS_::GetLightSensors(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getObstacleSensors (); */
NS_IMETHODIMP _MYCLASS_::GetObstacleSensors(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean wasTapped (); */
NS_IMETHODIMP _MYCLASS_::WasTapped(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean wasShaken (); */
NS_IMETHODIMP _MYCLASS_::WasShaken(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isObstacleLeftSide (); */
NS_IMETHODIMP _MYCLASS_::IsObstacleLeftSide(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isObstacleRightSide (); */
NS_IMETHODIMP _MYCLASS_::IsObstacleRightSide(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getLeftLightSensor (); */
NS_IMETHODIMP _MYCLASS_::GetLeftLightSensor(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getRightLightSensor (); */
NS_IMETHODIMP _MYCLASS_::GetRightLightSensor(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double getXAcceleration (); */
NS_IMETHODIMP _MYCLASS_::GetXAcceleration(double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double getYAcceleration (); */
NS_IMETHODIMP _MYCLASS_::GetYAcceleration(double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double getZAcceleration (); */
NS_IMETHODIMP _MYCLASS_::GetZAcceleration(double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isBeakUp (); */
NS_IMETHODIMP _MYCLASS_::IsBeakUp(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isBeakDown (); */
NS_IMETHODIMP _MYCLASS_::IsBeakDown(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isFinchLevel (); */
NS_IMETHODIMP _MYCLASS_::IsFinchLevel(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isFinchUpsideDown (); */
NS_IMETHODIMP _MYCLASS_::IsFinchUpsideDown(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isRightWingDown (); */
NS_IMETHODIMP _MYCLASS_::IsRightWingDown(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isLeftWingDown (); */
NS_IMETHODIMP _MYCLASS_::IsLeftWingDown(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double getTemperature (); */
NS_IMETHODIMP _MYCLASS_::GetTemperature(double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFinch_h__ */
