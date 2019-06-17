#include "mbed.h"
Serial PC(USBTX, USBRX);
Serial BT(PTE0,PTE1);
int main() 
{   
    PC.format(8,SerialBase::None,1);
    BT.format(8,SerialBase::None,1);
    PC.baud(115200);
    BT.baud(115200);
    
    while(1) 
    {   
        if(BT.readable()==1)
        {
            PC.putc(BT.getc());
        }
        if(PC.readable()==1)
        {
            BT.putc(PC.getc());
        }
    }
}
