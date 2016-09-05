#ifndef _SerialDataLib
#define _SerialDataLib

#define STARTING_MARK  '('
#define ENDING_MARK    ')'

class SerialData{
  public:
  SerialData(unsigned char markCounts);
  ~SerialData();
  
  protected:
  const unsigned char Mark_Num;
  unsigned char curMarkCount;
  bool BeginningMark;
  bool isReadMark;
  char startingMark;
  char endingMark;
  String Str_mark;
  String Str_data;
  String *Str_pMarks;
  
  public:
  void setCommand(const char *mark);
  bool ReadData(char buf, String &mark, String &data);
  int StringToInt(String data, unsigned char eleNum);
};

SerialData::SerialData(unsigned char markCounts)
  : Mark_Num(markCounts){
    
  Str_pMarks = new String[Mark_Num];
  for(int i = 0; i < Mark_Num; i++){
    Str_pMarks[i] = "";
  }
  curMarkCount = 0;
  BeginningMark = false;
  isReadMark = false;
  startingMark = STARTING_MARK;
  endingMark = ENDING_MARK;
}

SerialData::~SerialData(){
  delete[] Str_pMarks;
}

void SerialData::setCommand(const char *mark){
  if(curMarkCount < Mark_Num){
    Str_pMarks[curMarkCount] = mark;
    curMarkCount++;
  }
}

bool SerialData::ReadData(char buf, String &mark, String &data){
  if(buf == '\r' || buf == '\n' || buf == '\0')return false;
  if(BeginningMark){
    if(buf != startingMark);
    else{
      isReadMark = false;
      Str_mark = "";
      Str_data = "";
      return false;
    }
  }else{
    if(buf == startingMark)BeginningMark = true;
    return false;
  }
  if(isReadMark){
    if(buf == endingMark){
      bool isSubscribed = false;
      for(int i = 0; i < Mark_Num; i++){
        if(Str_mark == Str_pMarks[i])isSubscribed = true;
      }
      BeginningMark = false;
      isReadMark = false;
      if(isSubscribed){
        mark = Str_mark;
        data = Str_data;
        Str_mark = "";
        Str_data = "";
        return true;
      }else{
        mark = "";
        data = "";
        Str_mark = "";
        Str_data = "";
        return false;
      }
    }else{
      Str_data += buf;
    }
  }else{
    if(buf == endingMark){
      isReadMark = true;
    }else{
      Str_mark += buf;
    }
  }
  return false;
}


int SerialData::StringToInt(String data, unsigned char eleNum){
  unsigned char counter = 0;
  unsigned char len = data.length();
  String buf = "";
  
  for(int i = 0; i < len; i++){
    if(eleNum != counter){
      if(data[i] == ',')counter++;
    }else{
      if(data[i] == ',')break;
      else buf += data[i];
    }
  }
  if(buf != "")return buf.toInt();
  else return -1;
}


#endif
