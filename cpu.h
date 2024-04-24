void interruptEnable ();
void interruptDisable();
void interruptMode (int mode);
void interruptHalt (void);
void interruptVector (void (*func) (void));
void kickWatchdog (void);

