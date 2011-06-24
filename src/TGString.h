#ifndef _TGString_New_H_
#define _TGString_New_H_

// Version Oktober 2010 (r) Mollitz
// November 2010: erweritert von Matthias
// Januar 2011: f�r BADA erweitert von Matthias

//#define _BADA_

#include <string>
#include <sstream>


#ifdef _BADA_
#include <FText.h>
using namespace Osp::Text;
#endif


class TGString : public std::string
{
public:
    inline TGString() : std::string() {};
    inline TGString(const char*  str )      : std::string(str) {};
    inline TGString(const std::string &str) : std::string(str) {};
    inline TGString(const TGString    &str) : std::string(dynamic_cast<const std::string&>(str)) {};
    TGString(int           val); //decimal base
    TGString(unsigned int  val); //decimal base
    TGString(long          val);
    TGString(unsigned long val); //base 10
    TGString(long long     val);
    TGString(unsigned long long val); //base 10
    TGString(double val);
    ~TGString() {};

    TGString operator+=(int           val); //base 10
    TGString operator+=(unsigned int  val); //base 10
    TGString operator+=(long          val); //base 10
    TGString operator+=(unsigned long val); //base 10
    TGString operator+=(long long     val); //base 10
    TGString operator+=(unsigned long long val); //base 10
    TGString operator+=(double        val);
    TGString operator+=(bool          val);
    TGString operator+=(const TGString &str);

    TGString operator= (const char *str);
    TGString operator= (const TGString str);
    TGString operator= (int           val); //base 10
    TGString operator= (unsigned int  val); //base 10
    TGString operator= (long          val); //base 10
    TGString operator= (unsigned long val); //base 10
    TGString operator= (long long     val); //base 10
    TGString operator= (unsigned long long val); //base 10
    TGString operator= (double        val);
    TGString operator= (bool          val);
    
    TGString operator+ (int           val); //base 10
    TGString operator+ (unsigned int  val); //base 10
    TGString operator+ (long          val); //base 10
    TGString operator+ (unsigned long val); //base 10
    TGString operator+ (long long     val); //base 10
    TGString operator+ (unsigned long long  val); //base 10
    TGString operator+ (double        val);
    TGString operator+ (bool          val);
    TGString operator+ (void *p);
    TGString operator+ (const char *str);
    TGString operator+ (TGString str);

    long long toInt64();//base 10
    unsigned long long toUInt64();//base 10

    long          toInt (int base = 10); //base between 2 and 36
    unsigned long toUInt(int base = 10); //base between 2 and 36
    double        toDouble();            //If no valid conversion could be performed, a zero value is returned
    bool          toBool();

    TGString add(int val,          int base = 10); //base 8, 10 or 16
    TGString add(unsigned int val, int base = 10); //base 8, 10 or 16

#ifdef _BADA_
   TGString(Osp::Base::String val) : std::string()
   {
      if(val.GetLength())
      {
         Osp::Text::Utf8Encoding aEncoding;
         Osp::Base::ByteBuffer* buffer = aEncoding.GetBytesN( val );
         assign(TGString( reinterpret_cast<const char*>( buffer->GetPointer() )));
      }
   }

   TGString operator+=(Osp::Base::String val)
   {
      if(val.GetLength())
      {
         Osp::Text::Utf8Encoding aEncoding;
         Osp::Base::ByteBuffer* buffer = aEncoding.GetBytesN( val );
         append(TGString( reinterpret_cast<const char*>( buffer->GetPointer() )));
      }
      return *this;
   }
   TGString operator= (Osp::Base::String val)
   {
      if(val.GetLength())
      {
         Osp::Text::Utf8Encoding aEncoding;
         Osp::Base::ByteBuffer* buffer = aEncoding.GetBytesN( val );
         assign(TGString( reinterpret_cast<const char*>( buffer->GetPointer() )));
      }
      return *this;
   }
   TGString operator+ (Osp::Base::String val)
   {
      return operator+ (val.GetPointer());
   }

   Osp::Base::String o_str() {return Osp::Base::String(c_str());}
#endif
};

#endif  // define TGString
