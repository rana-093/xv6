#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sock.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
int a = 10;
struct {
  struct spinlock lock;
  struct sock sock[NPROC];
} stable;


//
// TODO: Create a structure to maintain a list of sockets
// Should it have locking?
//

void
sinit(void)
{
  //
  // TODO: Write any initialization code for socket API
  // initialization.
  //
  initlock(&stable.lock, "stable");
}

//10 ---> Server Port
int
listen(int lport) {
  //
  // TODO: Put the actual implementation of listen here.
  //
  cprintf("Bal amar : %d\n",lport);
  acquire(&stable.lock);	
  for(int i=0; i<NSOCK; i++){
	if(stable.sock[i].localport==10 && stable.sock[i].state==Listen){
		goto Listening;
	}
  }
  for(int i=0; i<NSOCK; i++){
	if(stable.sock[i].state!=Listen && stable.sock[i].state!=Connect){
		stable.sock[i].state = Listen;
		stable.sock[i].localport = lport;
		break;
	}
  }
  release(&stable.lock);
  return 0;
  Listening:
  release(&stable.lock);
  return -1;
}

int
connect(int rport, const char* host) {
  //
  // TODO: Put the actual implementation of connect here.
  //
	acquire(&stable.lock);	
  	int d = -1;
	for(int i=0; i<NSOCK; i++){
	if(stable.sock[i].localport==rport && stable.sock[i].state == Listen){
		d = i;
		goto NewPort;		
			
	}
      }
 release(&stable.lock);
 return -1;

NewPort:
	for(int i=0; i<NSOCK; i++){
	if(stable.sock[i].state!=Listen && stable.sock[i].state!=Connect){
		stable.sock[i].remoteport = rport;
		stable.sock[i].state = Listen;
		stable.sock[i].localport = 120;
		stable.sock[d].remoteport = 120;
		d = 120;
		break;
	}
     }
        release(&stable.lock);
  return d;
}

int
send(int lport, const char* data, int n) {
  //
  // TODO: Put the actual implementation of send here.
  //

  return 0;
}


int
recv(int lport, char* data, int n) {
  //
  // TODO: Put the actual implementation of recv here.
  //

  return 0;
}

int
disconnect(int lport) {
  //
  // TODO: Put the actual implementation of disconnect here.
  //

  return 0;
}
