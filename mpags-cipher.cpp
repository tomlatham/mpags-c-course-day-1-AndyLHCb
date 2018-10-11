#include <iostream>
#include <vector>
#include <string>

void printHelp();
bool dealWithInputs(const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFileName, std::string& outputFileName);

int main(int argc, char* argv[])
{
  const std::vector<std::string> cmdLineArgs { argv, argv+argc };

  const std::string versionNumber{"0.2"};

  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFileName{""};
  std::string outputFileName{""};
  if( ! dealWithInputs(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName) )
  {
    return 1;
  }

  // Handle help, if requested
  if (helpRequested) {
    printHelp();
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << versionNumber << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Warn that input file option not yet implemented
  if (!inputFileName.empty()) {
    std::cout << "[warning] input from file ('"
              << inputFileName
              << "') not implemented yet, using stdin\n";
  }

  // Loop over input
  std::cout<< "type something, then press Enter and Ctrl-D" <<std::endl;
  while(std::cin >> inputChar)
  {
    // Uppercase alphabetic characters
    if (std::isalpha(inputChar)) {
      inputText += std::toupper(inputChar);
      continue;
    }

    // Transliterate digits to English words
    switch (inputChar) {
      case '0':
	inputText += "ZERO";
	break;
      case '1':
	inputText += "ONE";
	break;
      case '2':
	inputText += "TWO";
	break;
      case '3':
	inputText += "THREE";
	break;
      case '4':
	inputText += "FOUR";
	break;
      case '5':
	inputText += "FIVE";
	break;
      case '6':
	inputText += "SIX";
	break;
      case '7':
	inputText += "SEVEN";
	break;
      case '8':
	inputText += "EIGHT";
	break;
      case '9':
	inputText += "NINE";
	break;
    }

    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
  }

  // Output the transliterated text
  // Warn that output file option not yet implemented
  if (!outputFileName.empty()) {
    std::cout << "[warning] output to file ('"
              << outputFileName
              << "') not implemented yet, using stdout\n";
  }

  std::cout << inputText << std::endl;

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



bool dealWithInputs(const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFileName, std::string& outputFileName)
{
  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

  // Process command line arguments
  // i starts at 1 to skip the program name
  for(size_type i{1};i<nCmdLineArgs;i++)
  {
    const std::string& arg = cmdLineArgs[i];

    if(arg == "-h" || arg == "--help")
    {
      helpRequested = true;
    }

    else if(arg == "--version")
    {
      versionRequested = true;
    }

    else if(arg == "-i")//input file
    {
      if(i != nCmdLineArgs-1)
      {
	inputFileName = cmdLineArgs[i+1];
	++i;//the next argument is just the name
      }
      else
      {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	return false;
      }
    }

    else if(arg == "-o")//output file
    {
      if(i != nCmdLineArgs-1)
      {
	outputFileName = cmdLineArgs[i+1];
	++i;//the next argument is just the name
      }
      else
      {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	return false;
      }
    }

    else
    {
      //if nothing's been triggered, input error
      std::cerr << "[error] unknown argument '" << arg << "'\n";
      return false;
    }

  }

  return true;
}
