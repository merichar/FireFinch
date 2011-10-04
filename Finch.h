#ifndef _FINCH_H_
#include "IFinch.h"
#include "xpcom-config.h"
#define FINCH_CONTRACTID "@rfmedialab.net/XPCOMFinch/Finch;1"
#define FINCH_CLASSNAME "Finch XPCOM"
#define FINCH_CID { \
    0xc901edf0, \
    0xddb9, \
    0x11e0, \
      {0x95, 0x72, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66} \
}  

class Finch : public IFinch
{
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFINCH

    Finch();



 private:
  ~Finch();
  int connect();
  int disConnect();
  int setLED(int red, int green, int blue);
  int counter();
  void keepAlive();
  int finchRead(unsigned char bufToWrite[], unsigned char bufRead[]);
  int finchWrite(unsigned char bufToWrite[]);
  static void* keepAliveEntryPoint(void * pThis)
    {  
        Finch * pthX = (Finch*)pThis;   // cast from void to Finch object
        pthX->keepAlive();           // now call the true entry-point-function


        return 0;          // the thread exit code
    }


 protected:
  /* additional members */
};

#endif
