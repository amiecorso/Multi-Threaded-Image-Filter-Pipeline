#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Blur br[50];
    br[0].SetInput(reader.GetOutput());
    for(int i = 1; i < 50; i++){
        br[i].SetInput(br[i-1].GetOutput());
    }
    
    br[49].GetOutput()->Update();
    fprintf(stderr,"HERE");

    PNMwriter writer;
    writer.SetInput(br[49].GetOutput());
    writer.Write(argv[2]);
    fprintf(stderr,"\n");
}
