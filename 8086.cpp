
#include<stdio.h>


void printbinary(unsigned char data){
	
	for(int i = 7; i >= 0; i--) {
		
		unsigned char bit = (data >> i) & 1;
		printf("%u", bit);
		
	}
	
	printf("\n");
	
}

int main()
{
	
	
	
	
	FILE *outputFile = fopen("output.asm", "w");
	if (outputFile == NULL) {
		
        printf("Error opening the output file.\n");
        return 1; // Indicate an error
		
    }
	
	
	
	char ByteReg[8][3] = {"AL","Cl","DL","BL","AH","CH","DH","Bh"};
	char WordReg[8][3] ={"AX","CX","DX","BX","SP","BP","SI","DI"};
	
	char Registers[8][20] = {"BX + SI","BX + DI","BP + SI","BP +DI " ,"SI","DI","Direct Address","BX"};
	
	//open a file to read the two bytes 
	FILE *fp =  fopen ("../listing_0038_many_register_mov.txt" , "rb" );
	if(fp==NULL){
		
		printf("error opening a file\n");
		return 0;
		
	}
	
	//put binary data into two bytes
	unsigned char InstDecodeBuffer[2];
	size_t bytesread;
	while((bytesread = fread(InstDecodeBuffer,  1,  2, fp))==2)
	{
		
		
		
		//printbinary(InstDecodeBuffer[0]);
		
		char mov  = InstDecodeBuffer[0] >> 2;
		
		if(mov == 0b100010){ // check if instruction is mov  
			//printf("SUCCESS\n");
			// TODO(shaheer read the other 8 bits for the program):
			
			char Dmask = 0b00000010;
			char Wmask = 0b00000001;
			char Dbit  =InstDecodeBuffer[0] & Dmask;
			char Wbit  =InstDecodeBuffer[0] & Wmask;
			char mod=(InstDecodeBuffer[1] & 0b11000000) >> 6;
			char reg=(InstDecodeBuffer[1] & 0b00111000) >> 3;
			char rm=InstDecodeBuffer[1] & 0b00000111;
			char Source;
			char Destination;
			char *reg1;
			char *reg2;
			
			//printf("this is mod ");
			//printbinary(mod);
			//printf("This is the Dbit ");
			//printbinary(Dbit);
			//printf("This is the W bit ");
			//printbinary(Wbit);
			//
			
			//printbinary(mov);
			
			if(mod == 0b11){
				
				//printf("SUCCESS\n");
				
				//both of the reg field and the mod field and the r/m field encode a register):
				// TODO(check which field is the reg field and which field is the mod field):
				
				if(Dbit==0b0){
					//instruction source is generated reg field 
					Source = reg;
					Destination = rm;
					//printbinary(Source);
				}
				else{
					// destination is in the reg field
					Source = rm;
					Destination = reg;
					
					//printbinary(Source);
					
				}
				
				
				
				if(Wbit==0b0){
					//use byte
					reg2 = ByteReg[Destination];
					reg1 = ByteReg[Source];
					
				}
				else{
					
					reg2 = WordReg[Destination];
					reg1 = WordReg[Source];
					
					//use word
					
				}
				
				//check which register is in the rm feild 
				
			}
			else if(mod == 0b00) 
			{
				
				if(rm != 0b110)
				{
					
					if(Dbit==0b0)
					{
						//instruction source is generated reg field 
						Source = reg;
						Destination = rm;
						
						//printbinary(Source);
					}
					else
					{
						// destination is in the reg field
						Source = rm;
						Destination = reg;
						
						//printbinary(Source);
					}
					
				}
				
				
				//// TODO(different mod figure out later what to do):
				
				
			}
			
			else if(mod == 0b01)
			{
				
				
				
				
			}
			
			else if(mod == 0b10)
			{
				
				
				
				
			}
			
			fprintf(outputFile, "mov %s, %s\n", reg2, reg1);
			printf("mov %s %s \n",reg2,reg1);
			
			
		}
		else{
			
			
		}
		
		
		
	}
	
}
