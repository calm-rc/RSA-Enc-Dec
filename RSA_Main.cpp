//
//  RSA final.cpp
//  Computer Science Project
//  Copyright (c) 2013 Rohan Chandrashekar. All rights reserved.
//

//***************************************************************
// HEADER FILES USED IN PROJECT
//***************************************************************

			#include<conio.h>
			#include<fstream>
			#include<iostream>	  	  	  
			#include<math.h>					
			#include<time.h>
			#include<windows.h>
			
			using namespace std;   	   	   

//***************************************************************
// IMPLEMENTING THE RSA ALGORITHM
//***************************************************************

struct RSA{
	int p,q,temp;
	long int e,d,n,totient,z[25];
	public:
	RSA()
	{
		p=q=0;
		temp=1;	   	   	   	   	   
	}
	
	int checkprime(int b)										//Function to check whether two numbers are prime or not.														
	{
		if(b<10)
		{
			return 1;
		}
		temp=0;
		for(int i=1;i<=int(sqrt(b));i++)
		{
			if(b%i==0)
			{
				temp++;
			}
		}
		if(temp>1)
		{
			return 1;
		}
		else 
		return 0;
	}
	
	int checkcoprime(int c,int f)								//Function to check whether two numbers are coprime or not.
	{
		while(1)
   		{
	        temp = c%f;
        	if(temp==0)
        	{
				return f;
			}
        	c = f;
        	f = temp;
		}
    }
		
	void euler(int g,int h)										//Euler function (to calculate n and public key).
	{
		n=g*h;
		totient=(g-1)*(h-1);
		cout<<"\n\n\tSelect Public key(e) such that - \n\n\t" 
			<<"1.e is not an even number.\n\t"
			<<"2.10<e<"<<totient<<" : " ;
			
		cin>>e;
		temp=1;
		while(temp)
		{
			if((e<10 || e>totient) || e%2==0 || checkcoprime(totient,e)!=1) 
			{
				cout<<"\n\tInvalid 'e'. Re-enter: ";
				cin>>e;
				temp=1;
			}
			else 
			{ 
				temp=0;
			}
		}
	}

	void privatekey()											//Function to calculate a random privatekey.
	{
		temp=0;
		for(int i=1;temp<25;i++)
		{
			if((i*e)%totient==1)
		 	{
				z[temp]=i;
				temp++;
		 	}
		}	 	 	 
		temp=rand() % 25;
		d=z[temp];	 
	}

	void keys()													//Function to accept two primes and set public and private key values.	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 
	{
		cout<<"\n\n\t\t******* Default Encryption/Decryption key(s) *******"
			<<"\n\n\n\tTip: Select large prime numbers and a large public key value\n\n\t\t\t   for better encryption.\n"
			<<"\n\tEnter the 1st prime number ( >10 ): ";
		cin>>p;
		while(checkprime(p))
		{
			if(p<10)
			{
				cout<<"\n\tNumber less than 10. Re-enter: ";
			}
			else
			{
				cout<<"\n\tNot a Prime. Re-enter: ";
			}
			cin>>p;
		}
		cout<<"\n\n\tEnter the 2st prime number ( >10 ): ";
		cin>>q;
		while(checkprime(q) || p==q)
		{
			if(q<10)
			{
				cout<<"\n\tNumber less than 10. Re-enter: ";
			}
			else if(q==p) 
			{
				cout<<"\n\tNumber already accepted. Re-enter: ";
			}
			else
			{
				cout<<"\n\tNot a Prime. Re-enter: ";
			} 
			cin>>q;
		}
		euler(p,q);
		privatekey();
		cout<<"\n\n\t\t  Public key: ("<<e<<","<<n<<")\tPrivate key: "<<d
			<<"\n\n\n\tNote: Please remember private key for decrypting data."
			<<"\n\n\n\t\t\tPress any key to continue.";
			getch();
		system("CLS");
	} 	  	    
};																//RSA structure ends here.


//***************************************************************
// DYNAMIC DATA STRUCTUE (QUEUE) CLASS
//***************************************************************
	 	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   

class queue{
	int data;
	queue *next,*front,*rear;
	public:
	
	queue()
	{
		next=0;
		front=rear=0;
	}
	
	void queueinsert(int v)										//Queue Insert function.
	{
		queue *tmp= new queue;
		if(tmp)
		{
			tmp->data=v;
			tmp->next=0;
			if(!front)
			{
				front=rear=tmp;
			}
			else 
			{
				rear->next=tmp;
				rear=tmp;
			}
		}			
	}
	
	int queuedelete(int &v)										//Queue Delete function.
	{
		if(front)
		{
			queue *tmp=front;
			v=front->data;
			front=front->next;
			delete tmp;
			if(!front)
			{
				rear=0;
			}
		return 1;
		}
		else 
		return 0;
	}
};																//Class queue ends here.

//***************************************************************
// ENCRYPTION/DECRYPTION CLASS 
//***************************************************************	 	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   

class encdec:public queue{
	int d1,file,fenc,temp;
	long int b,num,integer,arr[256];
	char ch,message[256],filename[256],fileext[8];
	public:
	
	encdec()
	{
		message[0]='\0';
		filename[0]='\0';
		fileext[0]='\0';
		num=arr[0]=0;
		fenc=temp=0;
	}	 
	
	int accept(int b)	   	   	   	   	   	   	   	   	   	   //Function to accept an integer, a message or a file name/location.									
	{
		cout<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\t";
		switch(b)
		{
			case 1:
			{	
				cout<<"\n\n\tEnter an integer: ";
				cin>>integer;
				num=0;
				return 1; 
			}
			break;
			case 2:
			{
				message[0]='\0';
				cout<<"\n\n\tEnter message: ";	 cin.get();
				cin.getline(message,256);
				arr[0]=0;
				return 1;
			}	
			break;
			case 3:
			{
				file=0;	  
				filename[0]='\0';
				cout<<"\n\n  Enter filename/file location (.txt only): ";	
					cin.get();
					cin.getline(filename,256);
					fstream f(filename);
					if(!f)
					{
						system("CLS");
						cout<<"\n\n\t\t\t    File doesnt not exist."
							<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\n\t";	  	  	  	  	   
						file=1;
					}
					else 
					{
						for(int i=0,j=0;filename[i];i++)
						{
							if(filename[i]=='.' || temp)
							{
								fileext[j]=filename[i];
								j++;	temp=1;
							}
							fileext[j+1]='\0';
						}
						if(strcmp(fileext,".txt"))
						{
							cout<<"\n\n  This is not a '.txt' file. Do you still want to continue ? (0 to exit): ";
							cin>>temp;
							if(temp)
							{
								return 1;	 
							}
							else 
							{
								return 0;
							}
						}	 
							
					}
					f.close();		
			}
			break;  
		}	    		
	}
	
	void encrypt(int c,RSA &a)									//Function to encrypt data. 
	{
		switch (c)
		{
			case 1:
			{	
				num=integer;
				for(int i=1;i<a.e;i++)
				{
					num=(num*integer)%a.n;
				}
				cout<<"\n\n\t\t\tEncrypted integer is :"<<num
					<<"\n\n\t\t\tPress any key to continue.";
					getch();
			}
			break;
			case 2:
			{
				for(int i=0;message[i];i++)
				{
					num=int(message[i]);
					b=num;
					for(int j=1;j<a.e;j++)
					{
						num=(num*b)%a.n;
					}
					arr[i]=num;
				}
				cout<<"\n\n\t\tEncrypted message is: ";
				for(int i=0;message[i];i++)
				{
					cout<<char(arr[i]);
				}
					cout<<"\n\n\t\t\tPress any key to continue.";
					getch();
			}
			break;
			case 3:
			{	
				if(file)
				{
					
					cout<<"\n\n\t\t\t     No file to encrypt."; getch();
					system("CLS");
					cout<<"\n\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\n\t";					
				}
				else 
				{
					fstream f(filename,ios::binary | ios::in);
					num=f.get();
					while(!f.eof())
					{ 		   
						b=num;
						for(int i=1;i<a.e;i++)
						{
							num=(num*b)%a.n;
						}
						queue::queueinsert(num);
						num=f.get();
					}
					f.close();	
					ofstream fout(filename,ios::binary);
					{
						while(queue::queuedelete(fenc))
						{	
							fout.write((char*)&fenc,sizeof(fenc));
						}
					}	 
				cout<<"\n\n\t\t\tFile has been encrypted."
					<<"\n\n\t\t\tPress any key to continue.";
					getch();
				fout.close();
				}	 	 	 	 					 	 	 	 	 	 	 	 	  
			} 	  	  	  
		}	 	 	 	 
	}
	
	void decrypt(int f,RSA &a)									//Function to decrypt data.
	{
		cout<<"\n\t\tEnter your current private key value: ";
		cin>>d1;
		if(d1!=a.d)
		{
			system("CLS");
			cout<<"\n\n\t\t\t    Private key does not match.";
			cout<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\n\t";
		}
		else 
		{
			switch (f)
			{
				case 1:
				{
					if(!num)
					{
						cout<<"\n\n\tInteger has not yet been encrypted."
							<<"\n\n\tPress any key to continue.";
						getch();
					}
					else 
					{ 
						b=num;
						for(int i=1;i<d1;i++)
						{
							b=(b*num)%a.n;
						}
						cout<<"\n\n\tDecrypted integer is :"<<b
							<<"\n\n\tPress any key to continue.";
							getch();  	  	  	  	  
					}
				}
				break;
				case 2:
				{
					if(!arr[0])
					{
						cout<<"\n\n\tMessage has not yet been encrypted."
							<<"\n\n\t\t\tPress any key to continue.";
						getch();
					}
					else 
					{
						for(int i=0;message[i];i++)
						{
							num=arr[i];
							b=num;
							for(int j=1;j<d1;j++)
							{
								num=(num*b)%a.n;
							}
							arr[i]=num;
						}
							cout<<"\n\n\t\tDecrypted message is: ";
						for(int i=0;message[i];i++)
						{
							cout<<char(arr[i]);
						}
							cout<<"\n\n\t\t\tPress any key to continue.";
							getch();					
					}	     	   	 
				}
				break;
				case 3:
				{
					if(file)
					{
						cout<<"\n\n\t\t\t     No file to decrypt."; getch();
						system("CLS");
						cout<<"\n\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\n\t";					
					}
					else 
					{
						fstream f(filename,ios::binary|ios::in|ios::out);
						f.read((char*)&fenc,sizeof(fenc));
						num=fenc;
						while(!f.eof())
						{ 
							num=fenc;	   	   	   
							b=num;
							for(int i=1;i<d1;i++)
							{
								num=(num*b)%a.n;
							}
							queue::queueinsert(num);
							f.read((char*)&fenc,sizeof(fenc));
						} 
						f.close();
						ofstream fout(filename,ios::binary);
						{
							while(queue::queuedelete(fenc))
							{	
								ch=char(fenc);
								fout.write((char*)&ch,sizeof(ch));
							}
						}
						fout.close();	 
						cout<<"\n\n\t\t\tFile has been decrypted. "
						<<"\n\n\t\t\tPress any key to continue.";
						getch();
					}	 	 	 	 	 
				}	 	 	 	 	 	  	  	  	  	  	    	  	  	  	  	  	  	  	   
			} 				
		}
	}
	
	void displaytext()	  	  	  	  	  	  	  	 			 //Function to display file contents.
	{
		if(file)
		{
			cout<<"\n\n\tNothing to display";
		}
		else 
		{
			fstream f(filename,ios::in|ios::out);
			ch=f.get();
			cout<<"\n\n\t\t\t    File details:\n\n";
			while(!f.eof())
			{ 	  	  	  
				cout<<ch;
				ch=f.get();
			}		 
			f.close();
		}
	}	
			         	 	 
};																//Class encdec ends here.	   	   

//***************************************************************
// MAIN MENU STRUCTURE 
//***************************************************************  

struct menus
{
	void opening()												// Program beggining.
	{
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t       RSA ENCRYPTION/DECRYPTION PROGRAM\n\n\n";
	 	Sleep(600);   
		Sleep(500);
		cout<<"\t\t\t  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
		Sleep(1000);
		cout<<"\xDB\xDB\xDB\xDB";
		Sleep(500);
	  	cout<<"\xDB\xDB\xDB\xDB\xDB\xDB";
	 	Sleep(500);
		cout<<"\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
		Sleep(750);
		system("CLS");	
	}
	
	void mainmenu()												//Function to print mainmenu.
	{
		cout<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\n\t" 
		<<"Main Menu: \n\n\t" 
		<<"1.Encrypt/Decrypt an integer.\n\n\t"
  		<<"2.Encrypt/Decrypt a message.\n\n\t"
 		<<"3.Encrypt/Decrypt a file(.txt).\n\n\t"
		<<"4.Accept temporary keys. \n\n\t"
		<<"5.Change default keys. \n\n\t"
		<<"6.Load default keys. \n\n\t"
		<<"7.Exit the program. \n\n\t";
		cout<<"\n\t\t\tEnter your choice:-> ";
	}
	
	void submenu(int a)											//Function to print submenu.
	{
			cout<<"\n\n\tSub Menu\n\t"
			<<"1.Encrypt data.\n\t"
 			<<"2.Decrypt data.\n\t";
			if(a==1)
			{
				cout<<"3.Enter different integer.\n\t"
					<<"4.Display keys in use.\n\t"
					<<"5.Return to main menu. \n\t"	;
			}
			else if(a==2)
			{
				cout<<"3.Enter a different message.\n\t"
					<<"4.Display keys in use.\n\t"
					<<"5.Return to main menu. \n\t"	;	   	   	   
			}
			else 
			{
				cout<<"3.Enter different filename.\n\t"
					<<"4.Display keys in use.\n\t"
					<<"5.Display file details.\n\t"
					<<"6.Return to main menu. \n\t"	;
			}
			cout<<"\n\t\t\tEnter your choice:-> "; 
	}

	void subopt(int f,RSA &b,encdec &c,menus &d)				//Function to carry out submenu option tasks.
	{	 
		int smopt,z=1;
		system("CLS");
		if(c.accept(f))
		{
			do 
			{
				d.submenu(f);
				cin>>smopt;											//Accepting submenu option here.
				switch(smopt)
				{
					case 1:
					{
						c.encrypt(f,b);
					}	 	 	 
					break;
					case 2:
					{
						c.decrypt(f,b);
					}
					break;
					case 3:
					{	
						system("CLS");
						if(c.accept(f))
						{
						}
						else 
						{
							system("CLS");
							z=0;
						}
					}
					break;
					case 4:											//Function to display temporary keys.
					{
						cout<<"\n\n\t\tPublic key: ("<<b.e<<","<<b.n<<")\tPrivate key: "<<b.d;	  
					}
					break;	  	  	  	  	  
					default:
					{
						if(f==3 && smopt==5)
						{
							c.displaytext();
						}
						else if((f==3 && smopt!=6) || (f!=3 && smopt!=5))
						{
							system("CLS");
							cout<<"\n\t\t\t\tInvalid option.";
							cout<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\t";
						}
						else 
						{
							z=0; 
							system("CLS");
						}
					}
				}
			}while(z);
		}
		else 
		{
			system("CLS");
		}
	}
};																//Structure menus ends here.

//***************************************************************
// PROFILE STRUCTURE 
//*************************************************************** 

struct profile{
	char username[31],password[31],upassword[31],uusername[31],ch;
	int c,temp;
	profile()
	{
		username[0]='\0';
		password[0]='\0';
		upassword[0]='\0';
		uusername[0]='\0';
		c=0;
		temp=1;
	}
	
	int prodetails(RSA &a)										//Function to get username/password for program.
	{
		fstream f("RSAPRO.dat",ios::binary|ios::in);
		cout<<"\n\n\t\t******* RSA Encryption/Decryption Program *******\n\n\t\t";
			if(!f)
			{
				cout<<"\n\n\t\tEnter following details to start using the program:"
					<<"\n\n\n\n\t\tEnter username: ";
				cin.getline(username,31);
					while(strlen(username)>30)
					{
						cout<<"\n\n\tUsername length exceeded. Re-enter: ";
						cin.getline(username,31);
					}
				cout<<"\n\t\tEnter password: ";
				for(int i=0;temp;)
				{
					ch=getch();
        			if(ch!='\b' && ch!='\r')
					{
						password[i]=ch;
            			i++;
            			cout<<"*";
					}
					if(ch=='\b' && i>=1)
        			{
            			cout<<"\b \b";
            			i--;
        			}
        			if(ch=='\r')
        			{
            			password[i]='\0';
            			temp=0;
					}
				}
				cout<<"\n\n\n\t\tNote: Remember password to access the program again."
					<<"\n\n\n\t\t\tPress any key to continue.";
					getch();
				system("CLS");
					a.keys();
				system("CLS");
				{
					ofstream fout("RSAPRO.dat",ios::binary|ios::out);
					fout.write((char*)username, sizeof(username));
					fout.write((char*)password, sizeof(password));
					fout.write((char*)&a.e, sizeof(a.e));
					fout.write((char*)&a.d, sizeof(a.d));
					fout.write((char*)&a.n, sizeof(a.n));
					fout.close();
				}
				return 1;	 	 	 	 
			}
			else 
			{
					temp=1;
					f.seekg(ios::beg);
					f.read((char*)username,sizeof(username));
				cout<<"\n\n\t\t\tUsername: "<<username;
				cout<<"\n\n\t\t\tEnter password: ";
				for(int i=0;temp;)
				{
					ch=getch();
        			if(ch!='\b' && ch!='\r')
					{
						upassword[i]=ch;
            			i++;
            			cout<<"*";
					}
					if(ch=='\b' && i>=1)
        			{
            			cout<<"\b \b";
            			i--;
        			}
        			if(ch=='\r')
        			{
            			upassword[i]='\0';
            			temp=0;
					}
				}
					f.read((char*)password,sizeof(password));
				if(strcmp(upassword,password)==0)
				{
					f.read((char*)&a.e,sizeof(a.e));
					f.read((char*)&a.d,sizeof(a.d));
					f.read((char*)&a.n,sizeof(a.n));
					system("CLS");
					return 1;
				}
			   	else 
				{
					system("CLS");
					cout<<"\n\t\t\t\tInvalid password.";
					if(c<3)
					{
						c++;
						
					}
					if(c==3)
					{
						cout<<"\n\n     Note:If you have forgotten your password, delete the RSAPRO.dat file \n\t\tpresent in your program folder to reset the program."
							<<"\n\n    Caution: On doing so, your default public and private keys will be lost.";
					}
					return 0;
				} 
										
			}
		f.close(); 	   
	}

	void defaultkeys(RSA &a)									//Function to load default keys.
	{
		fstream f("RSAPRO.dat",ios::binary|ios::in);
		f.seekg(62L,ios::beg);
		f.read((char*)&a.e,sizeof(a.e));
		f.read((char*)&a.d,sizeof(a.d));
		f.read((char*)&a.n,sizeof(a.n));
			system("CLS");
		f.close();
	} 	  
};																//Structure profile ends here.

//***************************************************************
// MAIN FUNCTION  
//*************************************************************** 
		
int main()
{
		int mmopt,checkd;
		char checkpassword[31];
		srand(time(NULL));
		RSA r;	encdec e;	menus m;	profile p;
		m.opening();
		while(!p.prodetails(r));								//Accepting profile details here.
		{
			do 
			{
				m.mainmenu();	 	   	 	 
				cin>>mmopt;										//Accepting mainmenu option here.
				switch(mmopt)
				{
					case 1:
					{
						m.subopt(mmopt,r,e,m);
					}
					break;
					case 2:
					{
						m.subopt(mmopt,r,e,m);
					}
					break; 
					case 3:
					{
						m.subopt(mmopt,r,e,m);
					}
					break;
					case 4:										//Function to load temporary keys.
					{	
						system("CLS");
						cout<<"\n\n\t   Caution: This is being done at your own risk, assuming the user\n\t\t\t knows what he/she is doing. ";
						cout<<"\n\n\n\t\tEnter temporary public key values:"
							<<"\n\n\t\t1st value:";
							cin>>r.e;
						cout<<"\n\t\t2nd value:";
							cin>>r.n;	
						cout<<"\n\n\t\tEnter temporary private key value: ";
							cin>>r.d;
						system("CLS");
					}
					break;
					case 5:										//Function to change default keys.
					{
						int temp=1;
						char ch;
						system("CLS");
						fstream f("RSAPRO.dat",ios::binary|ios::in);
						cout<<"\n\n\t   Caution: If verification is unsuccessful, default keys will \n\t\t\t\t    be loaded\n "
							<<"\n\n\t\t\t******* Identity verfication ******* ";
						cout<<"\n\n\n\t\tEnter you password: "; cin.get();
							for(int i=0;temp;)
							{
								ch=getch();
        						if(ch!='\b' && ch!='\r')
								{
									checkpassword[i]=ch;
            						i++;
            						cout<<"*";
								}
								if(ch=='\b' && i>=1)
        						{
            						cout<<"\b \b";
            						i--;
        						}
        						if(ch=='\r')
        						{
            						checkpassword[i]='\0';
            						temp=0;
								}
							}
						cout<<"\n\n\tEnter your current default private key: ";
							cin>>checkd;
						f.seekg(66L,ios::beg);
						f.read((char*)&r.d,sizeof(r.d));
							if(strcmp(checkpassword,p.password)==0 && checkd==r.d)
							{
								system("CLS");
								cout<<"\n\n\t\t\t     Verification successful\n";
								r.keys();
								ofstream fout("RSAPRO.dat",ios::binary|ios::out);
								{
									fout.write((char*)p.username, sizeof(p.username));
									fout.write((char*)p.password, sizeof(p.password));
									fout.write((char*)&r.e, sizeof(r.e));
									fout.write((char*)&r.d, sizeof(r.d));
									fout.write((char*)&r.n, sizeof(r.n));
								}
								fout.close();
							}
							else 
							{
								p.defaultkeys(r);
								cout<<"\n\n\t\t Verification unsuccessful. Default keys loaded.";
								
							}  
					}
					break;
					case 6:										//Calling default keys function.
					{
						p.defaultkeys(r);						
						cout<<"\n\t\t\t\tDefault keys loaded.";					
					}
					break;
					default:
					{
						if(mmopt!=7)
						{
							system("CLS");
							cout<<"\n\t\t\t\tInvalid option.";
						}
					}	 	 	 	 
				}
			}while(mmopt!=7);
		}	 	 	 
}

//***************************************************************
// END OF PROJECT
//***************************************************************

