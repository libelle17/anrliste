#include <string>
#include <vector>
using namespace std;
#include "tr64.h"


static int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
  if(writerData == NULL)
    return 0;

  writerData->append(data, size*nmemb);

  return size * nmemb;
}

int holurl(const std::string url, std::string* bufp)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
  bufp->clear();
  hnd = curl_easy_init();
  if(hnd == NULL) {
    fprintf(stderr, "CURL-Verbindung gescheitert\n");
		return -1;
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
		return -2;
  }
  return 0;
} // int holurl(const std::string url, std::string* bufp)

// XML-Inhalt ermitteln
size_t holraus(const std::string xml,std::string item,std::string *ergp,size_t anf/*=0*/)
{
  const std::string von="<"+item+">", bis="</"+item+">";
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
} // size_t holraus(const std::string xml,std::string item,std::string *ergp;size_t anf=0)


tr64cl::tr64cl(std::string fbusr,std::string fbpwd):
	cred(fbusr+":"+fbpwd),
	FB("http://fritz.box:49000"),
  urlvs("/upnp/control/"),	
	servs("urn:dslforum-org:service:")
{
  // Initialize CURL connection
  curl_global_init(CURL_GLOBAL_DEFAULT);
  // if(!init(hnd, ("http://"+FB+controlURL).c_str())) { fprintf(stderr, "Connection initializion failed\n"); exit(EXIT_FAILURE); }
}

// ermittelt aus test3.sh mit curl ... --libcurl test3.c
int tr64cl::fragurl(const std::string zurl, const std::string zservT, const std::string action, std::string* bufp,const vector<string>* iname/*=0*/,const vector<string>* ival/*=0*/)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
	url=FB;
	if (zurl.find('/')!=string::npos) url+=zurl; else url+=urlvs+zurl;
	if (!zservT.find("urn:")) servT=zservT; else servT=servs+zservT;
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
	std::string postfield="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"\nxmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">\n<s:Body>\n<u:"+action+" xmlns:u=\""+servT+"\">\n";
	if (iname && ival)
		for(size_t vnr=0;vnr<iname->size() && vnr<ival->size();vnr++) {
			postfield+="<"+iname->at(vnr)+">"+ival->at(vnr)+"</"+iname->at(vnr)+">\n";
		}
	postfield+="</u:"+action+">\n</s:Body>\n</s:Envelope>";
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
} // string fragurl
