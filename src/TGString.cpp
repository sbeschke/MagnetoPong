#include "TGString.h"
#include <stdlib.h>

TGString::TGString(int val)
{
   std::stringstream s;
   s << val; 
   assign(s.str());
}

TGString::TGString(unsigned int val)
{
   std::stringstream s;
   s << val; 
   assign(s.str());
}

TGString::TGString(long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
}

TGString::TGString(unsigned long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
}

TGString::TGString(long long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
}

TGString::TGString(unsigned long long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
}

TGString::TGString(double val)
{
   std::stringstream s;
   s.precision(10);
   s << val;
   assign(s.str());
}

//---------------------------------------------------------------------------
	
TGString TGString::operator+=(int val)
{
   std::stringstream s;
   s << val; 
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(unsigned int val)
{
   std::stringstream s;
   s << val; 
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(long val)
{
   std::stringstream s;
   s << val;
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(unsigned long val)
{
   std::stringstream s;
   s << val;
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(long long val)
{
   std::stringstream s;
   s << val;
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(unsigned long long val)
{
   std::stringstream s;
   s << val;
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(double val)
{
   std::stringstream s;
   s.precision(10);
   s << val;
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator+=(bool val)
{
   std::stringstream s;
   s << val; 
   append(s.str());
   return (*this);
}
//---------------------------------------------------------------------------
	
TGString TGString::operator+=(const TGString &str)
{
   append(dynamic_cast<const std::string&>(str));
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator=(const char *str)
{
   assign(str);
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator=(const TGString str)
{
   assign(dynamic_cast<const std::string&>(str));
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (int val)
{
   std::stringstream s;
   s << val; 
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (unsigned int val)
{
   std::stringstream s;
   s << val; 
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (unsigned long  val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (long long     val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (unsigned long long val)
{
   std::stringstream s;
   s << val;
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (double val)
{
   std::stringstream s;
   s.precision(10);
   s << val;
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------

TGString TGString::operator= (bool val)
{
   std::stringstream s;
   s << val; 
   assign(s.str());
   return (*this);
}
//---------------------------------------------------------------------------
	
TGString TGString::operator+(int val)
{
   std::stringstream s; 
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------
TGString TGString::operator+ (unsigned int val)
{
   std::stringstream s; 
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+(long val)
{
   std::stringstream s;
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+ (unsigned long val)
{
   std::stringstream s;
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+(long long val)
{
   std::stringstream s;
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+ (unsigned long long val)
{
   std::stringstream s;
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+ (double val)
{
   std::stringstream s;
   s.precision(10); 
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+ (bool val)
{
   std::stringstream s; 
   s << (*this);
   s << val;
   return s.str();
}
//---------------------------------------------------------------------------

/*TGString TGString::operator+(void *p)
{
   return operator+((int)(p));
}*/
//---------------------------------------------------------------------------

TGString TGString::operator+(const char *str)
{
   std::stringstream s; 
   s << (*this);
   s << str;
   return s.str();
}
//---------------------------------------------------------------------------

TGString TGString::operator+(TGString str)
{
   std::stringstream s;
   s << (*this);
   s << str;
   return s.str();
}
//---------------------------------------------------------------------------

long long TGString::toInt64()
{
   std::stringstream s(*this);
   long long val;
   s >> val;
   return val;
}
//---------------------------------------------------------------------------

unsigned long long TGString::toUInt64()
{
   std::stringstream s(*this);
   unsigned long long val;
   s >> val;
   return val;
}
//---------------------------------------------------------------------------

long TGString::toInt(int base)
{
   return strtol(c_str(),NULL,base);
}
//---------------------------------------------------------------------------

unsigned long TGString::toUInt(int base)
{
   return strtoul(c_str(),NULL,base);
}
//---------------------------------------------------------------------------

double TGString::toDouble()
{
   return strtod(c_str(),NULL);
}
//---------------------------------------------------------------------------

bool TGString::toBool()
{
   bool b;
   std::stringstream s;
   s << (*this);
   s >> b;
   return b;
}
//---------------------------------------------------------------------------

TGString TGString::add(int val, int base)
{
   std::stringstream s;
   switch(base)
   {
   case 8:  s << std::oct << val; break;
   case 10: s << std::dec << val; break;
   case 16: s << std::oct << val; break;
   }; 
   append(s.str());
   return *this;
}
//---------------------------------------------------------------------------

TGString TGString::add(unsigned int val, int base)
{
   std::stringstream s;
   switch(base)
   {
   case 8:  s << std::oct << val; break;
   case 10: s << std::dec << val; break;
   case 16: s << std::oct << val; break;
   }; 
   append(s.str());
   return *this;
}
//---------------------------------------------------------------------------
