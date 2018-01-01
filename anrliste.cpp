#include "kons.h"
#include "DB.h"
#define VOMHAUPTCODE
#include "anrliste.h"
#include <curl/curl.h>

enum T_
{
 T_zu_schreiben,
 T_VorgbAllg,
 T_VorgbSpeziell,
 T_MusterVorgb,
 T_rueckfragen,
 T_autokonfschreib,
 T_MAX
}; // enum T_

char const *DPROG_T[T_MAX+1][SprachZahl]={
 // T_zu_schreiben
 {"zu schreiben: ","must write: "},
 // T_VorgbAllg
 {"VorgbAllg()","generalprefs()"},
 // T_VorgbSpeziell
 {"VorgbSpeziell()","specialprefs()"},
 // T_MusterVorgb
 {"MusterVorgb()","sampleprefs"},
 // T_rueckfragen
 {"rueckfragen()","callbacks()"},
 // T_autokonfschreib
 {"autokonfschreib()","autoconfwrite()"},
 {"",""}
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen; muss dann auf lgp zeigen;

using namespace std;

hhcl::hhcl(const int argc, const char *const *const argv):hcl(argc,argv)
{
} // hhcl::hhcl

hhcl::~hhcl()
{
} // hhcl::~hhcl

// wird aufgerufen in: rueckfragen, als virtualle Funktion von hcl::gcl0()
void hhcl::lgnzuw()
{
 hcl::lgnzuw();
 Txd.lgn=Tx.lgn=Txk.lgn;
} // void hhcl::lgnzuw

// wird aufgerufen in: main
void hhcl::getcommandl0()
{
 if (obverb) {
  cout<<violett<<"getcommandl0()"<<schwarz<<endl;
  obverb=0;
 }
 // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
 const char* const sarr[]={"language"};
 agcnfA.initd(sarr,sizeof sarr/sizeof *sarr);
 gcl0();
} // getcommandl0

void hhcl::VorgbAllg()
{
 Log(violetts+Tx[T_VorgbAllg]+schwarz);
} // void hhcl::VorgbAllg

void hhcl::VorgbSpeziell()
{
 Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
 MusterVorgb();
} // void hhcl::VorgbSpeziell

void hhcl::MusterVorgb()
{
 Log(violetts+Tx[T_MusterVorgb]+schwarz);
} // void hhcl::MusterVorgb

// wird aufgerufen in: main
void hhcl::lieskonfein()
{
 hcl::lieskonfein();
 lfd++;
 setzlog();
 if (nrzf) rzf=0;
} // void hhcl::lieskonfein

//wird aufgerufen in: main
int hhcl::getcommandline()
{
 Log(violetts+"getcommandline()"+schwarz);
 return 0;
} // int hhcl::getcommandline

// wird aufgerufen in: main
void hhcl::rueckfragen()
{
 Log(violetts+Tx[T_rueckfragen]+schwarz);
 if (rzf) {
  int lfd=-1;
  const char *const locale = setlocale(LC_CTYPE,"");
  if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
  vector<string> sprachen={"e","d"/*,"f","i"*/};
  if (agcnfA[++lfd].wert.empty()||rzf) {
   langu=Tippstrs(sprachstr.c_str()/*"Language/Sprache/Lingue/Lingua"*/,&sprachen,&langu);
   lgnzuw();
   agcnfA[lfd].setze(&langu);
  } // if (agcnfA
 } // if (rzf)
} // void hhcl::rueckfragen()

// wird aufgerufen in: main
void hhcl::autokonfschreib()
{
 Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Txk[T_ja]:Txk[T_nein]));
 if (rzf||obkschreib) {
 } // if (rzf||obkschreib)
} // void hhcl::autokonfschreib

// wird aufgerufen in: main
void hhcl::zeigueberschrift()
{
 char buf[20]; snprintf(buf,sizeof buf,"%.5f",versnr);
 ::Log(schwarzs+Txk[T_Programm]+blau+mpfad+schwarz+", V: "+blau+buf+schwarz,1,1);
} // void hhcl::zeigueberschrift

static int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
  if(writerData == NULL)
    return 0;

  writerData->append(data, size*nmemb);

  return size * nmemb;
}

size_t holraus(const std::string xml,std::string tag,std::string *ergp,size_t anf=0)
{
  const std::string von="<"+tag+">", bis="</"+tag+">";
  if (ergp) {
    ergp->clear();
    size_t p1=xml.find(von,anf);
    if (p1!=std::string::npos) {
      p1+=von.length();
      size_t p2=xml.find(bis,p1);
      if (p2!=std::string::npos) {
        *ergp=xml.substr(p1,p2-p1);
        return p2+bis.length();
      }
    }
  }
  return 0;
} // size_t holraus(const std::string xml,std::string tag,std::string *ergp;size_t anf=0)

// ermittelt aus test3.sh mit curl ... --libcurl test3.c
int fragurl(const std::string url, const std::string cred, const std::string servT, const std::string action,const std::string item, std::string* bufp)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
  bufp->clear();
  struct curl_slist *slist1=0;
  slist1 = curl_slist_append(slist1, "Content-Type: text/xml; charset=\"utf-8\"");
  slist1 = curl_slist_append(slist1, ("SoapAction: "+servT+"#"+action).c_str());
  hnd = curl_easy_init();
  if(hnd == NULL) {
    fprintf(stderr, "Failed to create CURL connection\n");
    exit(EXIT_FAILURE);
  }
  curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
  curl_easy_setopt(hnd, CURLOPT_USERPWD, cred.c_str());
  std::string postfield="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"\nxmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">\n<s:Body>\n<u:"+action+" xmlns:u=\""+servT+"\">\n<></>\n</u:"+action+">\n</s:Body>\n</s:Envelope>";
  if ((code=curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postfield.c_str()))!=CURLE_OK) {
    fprintf(stderr, "Fehler bei postfield [%s]\n", errorBuffer);
    return false;
  }
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)postfield.length());
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.37.0");
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(hnd, CURLOPT_IPRESOLVE, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA , bufp);
  curl_easy_setopt(hnd, CURLOPT_ERRORBUFFER, errorBuffer);
  // Retrieve content for the URL
  code = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  if(code != CURLE_OK) {
    fprintf(stderr, "Fehler beim Verbinden zu '%s' [%s]\n", url.c_str(), errorBuffer);
    exit(EXIT_FAILURE);
  }
  return 0;
} // string fragurl(const string url, const string cred, const string servT, const string action,const string item)

int holurl(const std::string url, std::string* bufp)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
  bufp->clear();
  hnd = curl_easy_init();
  if(hnd == NULL) {
    fprintf(stderr, "Failed to create CURL connection\n");
    exit(EXIT_FAILURE);
  }
  curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA , bufp);
  curl_easy_setopt(hnd, CURLOPT_ERRORBUFFER, errorBuffer);
  // Retrieve content for the URL
  code = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  if(code != CURLE_OK) {
    fprintf(stderr, "Fehler beim Verbinden zu '%s' [%s]\n", url.c_str(), errorBuffer);
    exit(EXIT_FAILURE);
  }
  return 0;
} // int holurl(const std::string url, std::string* bufp)

class anruf
{
  public:
  std::string id; //Id
  std::string type; //Type
  std::string caller; //Caller
  std::string called; //Called
  std::string callednumber; //CalledNumber
  std::string name; //Name
};

int hhcl::holanr()
{
  std::vector<std::string> tz;
  tz.push_back("Id");
  tz.push_back("Type");
  tz.push_back("Caller");
  tz.push_back("Called");
  tz.push_back("CalledNumber");
  tz.push_back("Name");
  tz.push_back("Numbertype");
  tz.push_back("Device");
  tz.push_back("Port");
  tz.push_back("Date");
  tz.push_back("Duration");
  tz.push_back("Count");

  // Ensure one argument is given


  curl_global_init(CURL_GLOBAL_DEFAULT);

  // Initialize CURL connection

  std::string credentials=usr+":"+pwd;
  std::string FB="fritz.box:49000";
  std::string controlURL="/upnp/control/x_contact";
  std::string serviceType="urn:dslforum-org:service:X_AVM-DE_OnTel:1";
  std::string action="GetCallList";
  std::string item="NewCallListURL";
  /*
  if(!init(hnd, ("http://"+FB+controlURL).c_str())) {
    fprintf(stderr, "Connection initializion failed\n");
    exit(EXIT_FAILURE);
  }
  */
  std::string buffer,nurl;
  fragurl("http://"+FB+controlURL,credentials,serviceType,action,item,&buffer);

  //std::cout<<buffer<<std::endl;
  holraus(buffer,item,&nurl);
  holurl(nurl,&buffer);
  size_t pos=0,enr=0;
  while ((pos=holraus(buffer,"Call",&nurl,pos))) {
    std::cout<<++enr<<": ";
    for(size_t tzn=0;tzn<tz.size();tzn++) {
      std::string it;
      holraus(nurl,tz[tzn],&it);
      std::cout<<it<<";";
    }
    std::cout<<std::endl;
  }

  // std::cout<<buffer<<std::endl;

  // Parse the (assumed) HTML code
  //  parseHtml(buffer, title);

  return EXIT_SUCCESS;
}

int main(int argc,char** argv)
{
 hhcl hhi(argc,argv); // hiesige Hauptinstanz
 /*//
 if (argc>1) {
 } // (argc>1)
 */
 hhi.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
 hhi.VorgbAllg();
 hhi.usr="libelle17";
 hhi.pwd="bach17raga";
 if (hhi.obhilfe==3) { // Standardausgabe gewaehrleisten
  hhi.MusterVorgb();
 } else {
  hhi.VorgbSpeziell(); // die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void hhcl::VorgbSpeziell()" ueberladbar sind
  hhi.lieskonfein();
 } // if (hhi.obhilfe==3)
 hhi.lieszaehlerein(&hhi.aufrufe,&hhi.tagesaufr,&hhi.monatsaufr,&hhi.laufrtag);

 if (hhi.getcommandline())
  exit(8);
 if (hhi.obvi) hhi.dovi();
 if (hhi.zeigvers) {
	 hhi.zeigversion();
 } // if (hhi.zeigvers)
 hhi.holanr();
 hhi.autokonfschreib();
 hhi.schlussanzeige();
 return 0;
} // int main
