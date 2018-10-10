#include <iostream>
#include <vector>
#include <string>

void printHelp();
int dealWithInputs(std::vector<std::string> cmdLineArgs);

std::string versionNumber{"0.2"};

std::string inputFileName{" "};
std::string outputFileName{" "};

bool skipFlag{0}; //sometimes we have to skip an argument




int main(int argc, char* argv[])
{
  const std::vector<std::string> cmdLineArgs { argv, argv+argc };

  if(dealWithInputs(cmdLineArgs)){return 1;}

  std::cout<< "type something, to exit type '-q'" <<std::endl;
  std::string manualInput;
  while(1)
  {
    std::getline(std::cin, manualInput);
    if(manualInput == "-q"){break;}
    std::cout << "you said: " << manualInput << std::endl;
    for (auto & c: manualInput) c = toupper(c);
    std::cout << "but you yelled: " << manualInput << std::endl;
  }
  
  //printing the output file names
  if(inputFileName != " "){std::cout << "The input file name is: " << inputFileName << std::endl;}
  if(outputFileName != " "){std::cout << "The output file name is: " << outputFileName << std::endl;}
  
  return 0;
}







void printHelp()
{
  std::cout << "This is the help message" << std::endl;
  std::cout << "The options are: -h --help --version -i -o" << std::endl;
  std::cout << "-i will specify an input file" << std::endl;
  std::cout << "-o will specify an output file" << std::endl;
  return;
}



int dealWithInputs(std::vector<std::string> cmdLineArgs)
{
  std::string arg;
  std::string nextArg;

  for(int i{1};i<cmdLineArgs.size();i++)//i starts at 1 to skip the program name
    {
      if(skipFlag){skipFlag = 0;continue;}//Skip this argument because it's a file name
      
      arg = cmdLineArgs[i];
      if(i != cmdLineArgs.size()-1){nextArg = cmdLineArgs[i+1];}

      if(arg == "-h" or arg == "--help"){printHelp();continue;}
      
      if(arg == "--version")
      {
	std::cout << "This is version:" << versionNumber << std::endl;
	continue;
      } // print version #

      
      if(arg == "-i")//input file
	{
	  inputFileName = nextArg;
	  skipFlag = 1;//the next argument is just the name
	  continue;
	}

      
      if(arg == "-o")//output file
	{

	  outputFileName = nextArg;
	  skipFlag = 1;//the next argument is just the name
	  continue;
	}

      
      std::cerr << "Input Error" << std::endl;return 1;//if nothing's been triggered, input error

    }
  return 0;
}
