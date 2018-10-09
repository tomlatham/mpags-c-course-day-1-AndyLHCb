/* I've started working on the caeser cipher early because I'm bored*/

#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>

const char abet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; //def the alphabet

const char Abet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; //upper case alphabet

std::string phrase; // phrase to be ciphered

std::string cipher(std::string input, bool direction); // the ciphering algorithm the bool decides whether we're ciphering or deciphering

void flagSet(int argc, char *argv[]); // this takes the user input arguments and works out what the program should do setting the flags accordingly
bool flags[5]={0,0,0,1,0};//Flags for various user inputs listed below
/*help, input, output, cipher/decipher, input error*/
int shiftLevel{1};

std::string inputcipher(); //lets you input a cipher if no input file is given

void printhelp();//prints the help statement

std::string readfilein(std::string inFile);//reads a file
void writefileout(std::string outFile);//writes a file

std::string inFileName;//input file name if needed
std::string outFileName;//output file name if needed

std::string output; //the actual ciphered phrase





  
int main(int argc, char *argv[]) //could be made prettier with switch cases, can't be bothered to learn how they work right now.
{
  flagSet(argc, argv);

  if(flags[0]==1){printhelp();return 0;}//if they ask for help, print help

  if(flags[4]==1){std::cerr<<"Input error, use '-h' to find good inputs"<<std::endl;return 1;}//error for bad input
  
  if(flags[1]==0){phrase = inputcipher();}//input manually if no input file
  else{phrase = readfilein(inFileName);}//read file in if specified

  output  = cipher(phrase,flags[3]);//the cipher
  if(flags[2]==0){std::cout << output << std::endl;} //print the cipher if no output file
  else{writefileout(outFileName);}//write file out if specified

  return 0;
}





std::string cipher(std::string input,bool direction)
{
  std::string ciphered; //the ciphered phrase
  if(!direction){shiftLevel *= -1;}

  for(char c : input)//running over the input
    {	 
      for(int i{0};i<26;i++)//running over the alphabet
      {
	int cryptno = ((i+shiftLevel)%26+26)%26; //setting up the replacement letter 
	
        if(abet[i]==c)
	{
	  //here begins the cipher
	  ciphered += abet[cryptno];
	  break;
	}
	else if(Abet[i]==c) // this is the same but for upper case
	{
	  ciphered += Abet[cryptno];
	  break;
	}
	else if(i==25){ciphered +=c;break;}
      }
    }
  return ciphered;
}

void flagSet(int argc, char *argv[])
{//this could definitely be done better with switch cases
  for(int i{1};i<argc;i++)
  {
    std::string currentArg = argv[i];//The current argument
    std::string prevArg = argv[i-1];//The previous argument
    
    if(currentArg == "--help"||currentArg == "-h"){flags[0]=1;}
    else if(currentArg == "-i"){flags[1]=1;inFileName = argv[i+1];}
    else if(currentArg == "-o"){flags[2]=1;outFileName = argv[i+1];}
    else if(currentArg == "-decipher"){flags[3]=0;}
    else if(currentArg == "-cipher"){flags[3]=1;}
    else if(currentArg == "-k"){shiftLevel = std::atoi(argv[i+1]);}
    
    else if(prevArg != "-i" and prevArg != "-o" and prevArg != "-k"){flags[4]=1;}//This is an input error
  }
  return;
}

std::string inputcipher()
{
  std::cout << "type a phrase to be ciphered" << std::endl;

  std::string input;
  std::getline(std::cin, input);
  std::cout << std::endl;
  return input;
}

void printhelp()
{
  std::cout<< std::endl << std::endl;
  std::cout<< "Welcome to my caeser encryptor, these are the options you may use:"<< std::endl;
  std::cout<< "'-i' to specify an input file (otherwise a code can be entered manually)"<<std::endl;
  std::cout<< "'-o' to specify an output file (otherwise the encryption will be outputted to console)"<<std::endl;
  std::cout << "'-k' to specify the shift amount (by default set to 1)" << std::endl;
  std::cout<< "'-cipher' or '-decipher' to choose a direction of ciphering (by default set to cipher)"<<std::endl;
  std::cout<< "'-h'or '--help' for this help page"<<std::endl;
  std::cout<< std::endl << std::endl;
  return;
}


std::string readfilein(std::string inFile)
{
  std::ifstream ifs{inFile};
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  return content;
}


void writefileout(std::string outFile)
{
  std::ofstream out(outFile);
  out << output;
  out.close();  
  return;
}
