#include <curl/curl.h>

size_t holraus(const std::string xml,std::string tag,std::string *ergp,size_t anf=0); // XML-Inhalt ermitteln
int holurl(const std::string url, std::string* bufp);

class tr64cl {
	public:
		string cred;
		string FB;
		string urlvs;
		string servs;
	private:
		string url;
		string servT;
	public:
		tr64cl(std::string fbusr,std::string fbpwd);
		int fragurl(const string zurl, const string zservT, const string action, string* bufp,const vector<string>* iname=0,const vector<string>* ival=0);
};
