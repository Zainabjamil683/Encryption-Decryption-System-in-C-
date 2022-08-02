#include<iostream>
#include<string>
#include<fstream>
#include<math.h>
using namespace std;
class Strategy 
{
	public:
	virtual string encryption_operation(string str)=0;
	virtual string decryption_operation(string str)=0;
};
class Cryptography
{
	public:
		string str;
	public:
		string getmsg()
		{
			cout<<"\n\n\t\tEnter String:- ";
			cin.ignore();
			getline(cin,str);
			return str;
		}
};
class Cesar:public Cryptography, public Strategy
{
	public:
		string encryption_operation(string str)
	 	{
		
			for (int i=0; str[i]!='\0';i++)
			{
				if((str[i]>=65)&&(str[i]<=90))	//uppercase
				{							
					str[i]=str[i]+3;			
					if(str[i]>90)				
					{							
						str[i]=str[i]-26;		
					}
				}
				else if((str[i]>=97)&&(str[i]<=122))	//lowercase
				{								
					str[i]=str[i]+3;			
					if(str[i]>122)				
					{
						str[i]=str[i]-26;		
					}
				}
			}
			return str;
		}
		string decryption_operation(string str)
		{
			for (int i=0; str[i]!='\0';i++)
			{
				if((str[i]>=65)&&(str[i]<=90))	//uppercase
				{							
					str[i]=str[i]-3;		
					if(str[i]<65)			
					{
						str[i]=str[i]+26;		
					}
				}
				else if((str[i]>=97)&&(str[i]<=122)	)//lowercase
				{							
					str[i]=str[i]-3;		
					if(str[i]<97)			
					{
						str[i]=str[i]+26;		
					}
				}
			}
			return str;
		}
};
class XOR:public Cryptography, public Strategy
{
	protected:
	char encryption_key = 'A';//A=0100 0001
	public:
	string encryption_operation(string str)
	{		
    	string out_string = "";
    	int i = 0,j=str.length();
    	while(i < j)	
    	{									
        	out_string += str[i] ^ encryption_key; //everytime add pervious number to form word
        	str[i]=out_string[i];
			i++;
    	}
    	return str;
	}
	string decryption_operation(string str)
	{
		string out_string = "";
   		 int i = 0,j=str.length();
    	while(i < j)	
    	{									
        	out_string += str[i] ^ encryption_key; //everytime add pervious number to form word
        	str[i]=out_string[i];
			i++;
    	}
    	return str;
    }
};
class RSA:public Cryptography,public Strategy
{
	protected:
 		long int fn, sn, n, t, flag, e[100], d[100], temp[100], m[100], em[100];
    public:
 	void set_prime()
 	{
 		cout << "\n\t\tEnter first prime number: ";
    	cin >> fn;
    	flag = check_prime(fn);
    	if (flag == 0)
    	{
        	cout <<"\n\t\twrong input\n";
        	exit(1);
    	}
    	cout << "\n\t\tenter another prime number: ";
    	cin >> sn;
    	flag = check_prime(sn);
    	if (flag == 0 || fn == sn)
    	{
        	cout << "\n\t\twrong input\n";
        	exit(1);
    	}	
	}
	 int check_prime(long int pr)
    {
        int i;
        for (i = 2; i <=sqrt(pr); i++)
        {
            if (pr % i == 0)
                return 0;
        }
        return 1;
    }
    void set_msg()
    {
    	for (int i = 0; str[i]!='\0'; i++)
       		 m[i] = str[i];
    	n = fn * sn;	
    	t = (fn - 1) * (sn - 1);
	}
	
	void sk()
    {
        int k=0;
        for (int i = 2; i < t; i++)
        {
            if (t % i == 0)		
                continue;
            flag = check_prime(i);
            if (flag == 1 && i != fn && i != sn)
            {
                e[k] = i;	
				flag = cd(e[k]);	
                if (flag > 0)
                {
                    d[k] = flag;
                    k++;
                }
                if (k == 99)
                    break;
            }
        }
    }
    long int cd(long int x)
    {
        long int k = 1;
        while (1)
        {
            k = k + t;	
            if (k % x == 0)	
            {
                return (k / x);	
			}
		}
    }
	string encryption_operation(string str)
	{
		long int pt, ct, key = e[0], k, len;
    	int i = 0;
    	len = str.length();	
    	while (i != len)
    	{		
        	pt = m[i];
        	pt = pt - 96; 
        	k = 1;
        	for (int j = 0; j < key; j++)
        	{
            	k = k * pt; 
            	k = k % n;
        	}	
        	temp[i] = k;	
        	ct = k + 96;	
        	em[i] = ct;		
    		i++;
    	}
    	em[i] = -1;
    	// encryption msg storing
    	for (i = 0; em[i] != -1; i++)
    	{
        	str[i]=em[i];
		}
		return str;
	}
	string decryption_operation(string str)
	{
    	long int pt, ct, key = d[0], k;
    	int i = 0;
    	while (em[i] != -1)
    	{
    		
        	ct = temp[i];
        	k = 1;
        	for (int j = 0; j < key; j++)
        	{
            	k = k * ct;
            	k = k % n;
        	}
        	pt = k + 96;
        	m[i] = pt;
        	i++;
		}
    	m[i] = -1;
    	//decryption msg  storing
    	for (i = 0; m[i] != -1; i++)
    	{
    		str[i]=m[i];
		}
		return str;
	}	
};
class Context {
   public: 
   Strategy *strategy;

   public: 
   Context()
   {
   }
   Context(Strategy *strategy){
      this->strategy = strategy;
   }
   string executeStrategy(string str){
       return strategy->encryption_operation(str);
   }
   string executeDecStrategy(string str){
		return strategy->decryption_operation(str);
   }
};
main()
{
	Cryptography cc;
	string result_enc,result_dec;
	int enc_choice,choice; char dec_choice;
	fstream cryptography;
	cout<<"\n\n\t\t**************** WELCOME to CRYPTOGRAPHY *****************\n\n";
	cout<<"\t\t**************** ENCRYPTION & DECRYPTION SYSTEM ***************\n\n\n";
	do{
		cout<<"\t\t 1. CESAR CIPHER\n\n";
		cout<<"\t\t 2. XOR CIPHER \n\n";
		cout<<"\t\t 3. RSA\n\n";
		cout<<"\t\t 4. Your Previous Encryption record\n\n";
		cout<<"\t\t 5. Exit\n\n\n";
		cout<<"\t\t======================================================="<<endl;
		cout<<"\t\t======================================================="<<endl;
		cout<<"\t\t Which type of encryption you want:";
		cin>>enc_choice;
		system("cls");
		switch(enc_choice)
		{
			case 1:	//cesar
			{
				cryptography.open("D:Cryptography.txt",ios::app);
				Context *c1= new Context(new Cesar());
				//encryption
				result_enc=c1->executeStrategy(cc.getmsg());
				if(cryptography.is_open())
				{
					cout<<"\n\t\tEncrpted message: "<<result_enc ;
					cryptography<<"CESAR Cipher\n";
					cryptography<<"Encrptyted message: "<<result_enc<<endl;
					cout<<"\n\n\t\tDo you want to decrypt: ";
					cin>>dec_choice;
					//decryption
					if(dec_choice=='y')
					{
						result_dec=c1->executeDecStrategy(result_enc);
						cout<<"\n\t\tDecrypted message: "<<result_dec<<endl;
						cryptography<<"decrypted message: "<<result_dec<<endl;
					}	
					cout<<"\n\t\tDo you To Encrypt Message again:\n\n";
					cryptography.close();
				}
				break;			
			}
			case 2:	//XOR
			{
				cryptography.open("D:Cryptography.txt",ios::app);
				Context *c2=new Context(new XOR());
				//Encryption
				result_enc=c2->executeStrategy(cc.getmsg());
				if(cryptography.is_open())
				{
					cout<<"\n\t\tEncrpted message: "<<result_enc ;
					cryptography<<"XOR\n";
					cryptography<<"Encrptyted message: "<<result_enc<<endl;
					cout<<"\n\n\t\tDo you want to decrypt: ";
					cin>>dec_choice;
					//decryption
					if(dec_choice=='y')
					{
						result_dec=c2->executeDecStrategy(result_enc);
						cout<<"\n\t\tDecrypted message: "<<result_dec<<endl;
						cryptography<<"decrypted message: "<<result_dec<<endl;
					}
				}
				cout<<"\n\t\tDo you To Encrypt Message again:\n\n";	
				cryptography.close();
				break;
			}
			case 3:	//RSA
			{	
				cryptography.open("D:Cryptography.txt",ios::app);
				string s;
				RSA r1;
				RSA *rpt=&r1;
				s=r1.getmsg();
				r1.set_prime();
				r1.set_msg();
				r1.sk();
				Context *c3=new Context(rpt);
				//Encryption
				result_enc=c3->executeStrategy(s);		
				if(cryptography.is_open())
				{
					cout<<"\n\t\tEncrpted message: "<<result_enc ;
					cryptography<<"RSA\n";
					cryptography<<"Encrptyted message: "<<result_enc<<endl;
					cout<<"\n\n\t\tDo you want to decrypt: ";
					cin>>dec_choice;
					//decryption
					if(dec_choice=='y')
					{
						result_dec=c3->executeDecStrategy(result_enc);
						cout<<"\n\t\tDecrypted message: "<<result_dec<<endl;
						cryptography<<"decrypted message: "<<result_dec<<endl;
					}
				}
				cout<<"\n\t\tDo you To Encrypt Message again:\n\n";	
				cryptography.close();
				break;
			}
			case 4:	//Showing file
			{
				cryptography.open("D:Cryptography.txt",ios::in);
				if(cryptography.is_open())
				{
					cout<<"\n\tYour Encryption Record\n\n";
					string ch;
					while(!cryptography.eof())
					{
						getline(cryptography,ch);
						cout<<"\t"<<ch<<endl;
					}	
				}
				break;
			}
			case 5:	//exit
			{
				cout<<"\n\n\t\t======================================================="<<endl;
				cout<<"\n\t\tTHANK YOU FOR USING OUR ENCRYPTION DECRYPTION SYSTEM\n\n";
				cout<<"\t\t======================================================="<<endl;
				cout<<"\n\t\t    ***********SYSTEM DESIGNED BY***********\n\n\t\t\t"; 
				cout<<" ZAINAB JAMIL  (2021 BSE 034)\n\n";
				cout<<"\n\t\t=======================================================\n"<<endl;
				exit(0);
				break;
			}
		}
	}while(choice!=4);
}