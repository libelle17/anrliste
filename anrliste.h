#define DPROG "anrliste"
class hhcl:public hcl
{
 private:
 public:
  uchar obvi=0; // ob Konfigurationsdatei editiert werden soll
	string usr;
	string pwd;
 private:
  void lgnzuw();
 public:
  hhcl(const int argc, const char *const *const argv);
  ~hhcl();
 void getcommandl0();
 void VorgbAllg();
 void VorgbSpeziell()
#ifdef VOMHAUPTCODE
 __attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
 ;
 void MusterVorgb();
 void lieskonfein();
 int getcommandline();
 void rueckfragen();
 int holanr();
 void autokonfschreib();
 void zeigueberschrift();
}; // class hhcl
