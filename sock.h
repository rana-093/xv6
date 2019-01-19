enum state {Closed,Listen,Connect};

struct sock{
int localport;                
int remoteport;  
int owner;
enum state state;        
char buf[128];
int dataAvailable;
};
