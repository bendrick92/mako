#define T_CLK 6
#define T_CS 5
#define T_DIN 4
#define T_DOUT 3
#define T_IRQ 2

#define X_CONST 320
#define Y_CONST 480

#define PixSizeX	1143
#define PixOffsX	1780

#define PixSizeY	793
#define PixOffsY	1380

class CTouch {
public:
	void init(void)
	{
		pinMode(T_CLK,  OUTPUT);
		pinMode(T_CS,   OUTPUT);
		pinMode(T_DIN,  OUTPUT);
		pinMode(T_DOUT, INPUT);
		pinMode(T_IRQ,  INPUT_PULLUP);

		digitalWrite(T_CS,  HIGH);
		digitalWrite(T_CLK, HIGH);
		digitalWrite(T_DIN, HIGH);
		digitalWrite(T_CLK, HIGH);
	}

	void writeData(unsigned char data)
	{
		unsigned char temp;
		unsigned char nop;
		unsigned char count;

		temp=data;
		digitalWrite(T_CLK,LOW);

		for(count=0; count<8; count++)
		{
			if(temp & 0x80)
				digitalWrite(T_DIN, HIGH);
			else
				digitalWrite(T_DIN, LOW);
			temp = temp << 1; 
			digitalWrite(T_CLK, LOW);                
			nop++;
			digitalWrite(T_CLK, HIGH);
			nop++;
		}
	}

	unsigned int readData()
	{
		unsigned char nop;
		unsigned int data = 0;
		unsigned char count;
		for(count=0; count<12; count++)
		{
			data <<= 1;
			digitalWrite(T_CLK, HIGH);               
			nop++;
			digitalWrite(T_CLK, LOW);
			nop++;
			data |= digitalRead(T_DOUT);
		}
		return(data);
	}

	bool read(int& x, int& y)
	{
		long tx=0;
		long ty=0;
               
		digitalWrite(T_CS,LOW);                    
		for (int i=0; i < 10; i++)
		{
			writeData(0x90);        
			digitalWrite(T_CLK,HIGH);
			digitalWrite(T_CLK,LOW); 
                        int d = readData();
			if (d >= 4000) {
                          return false;
                        }
			ty += d;

			writeData(0xD0);      
			digitalWrite(T_CLK,HIGH);
			digitalWrite(T_CLK,LOW);
			tx+=readData();
		}
		digitalWrite(T_CS,HIGH);
                y = Y_CONST - (ty - PixOffsY) * 10 / PixSizeY;
                x = X_CONST - (tx - PixOffsX) * 10 / PixSizeX;
                return true;
	}
};

CTouch touch;
