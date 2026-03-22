---
config:
  theme: neo-dark
---
classDiagram
direction TB
    class Request {
	    -std::string _method : GET, POST, DELETE...
	    -std::string _path : /index.html vs.
	    -std::string _version : HTTP/1.1 gibi
	    -std::map _headers : key value header'lar listesi.
	    -std::string _body : body tamami.
	    +Request()
	    +Request(const Request &ref)
	    +Request &operator=(const Request &ref)
	    +~Request()
	    +getter's / setter's() : header map oldugu icin key value mantigina dikkat. hasHeader(key), getHeader(key)
    }

    class ResponseFactory {
	    --- FACTORY METHOD DESIGN ---
        ---! Burada ornegin createResponse icerisindeki request referans olmasaydi buyuk request bufferi dahil her sey kopyalanirdi. !---
        +ResponseFactory()
        +~ResponseFactory()
	    IResponse *createResponse(Request &request) Request'e gore response olustur ve dondur.
    }

    class StaticResponse {
        -Request &_request
        -std::size_T _bodySize
        -void createBody()
        -const std::string getContentType() Uzantiya gore Content-Type header'i belirler.
        +StaticResponse(Request &request, std::size_t bodySize)
        +~StaticResponse()
        +std::string serialize() Response uretimi.
    }

    class ErrorResponse {
        --- Error page .conf'taki root'ta var mi kontrol, yoksa default. ---
        -void createBody()
        +ErrorResponse(StatusCode statusCode)
        +~ErrorResponse()
        +std::string serialize() Response uretimi.
    }

    class AutoIndexResponse {
        --- PLANLANMADI!!! ---
        -void createBody()
        +AutoIndexResponse()
        +~AutoIndexResponse()
        +std::string serialize() Response uretimi.
    }

    class CGIResponse {
        --- PLANLANMADI!!! ---
        +std::string serialize() Response uretimi.
    }

    class AResponseBase {
        --- Abstract Base ---
        #HTTPStatusCode _statusCode : 404, 400, 200 vs.
        #HTTPStatusMessage _statusMessage : Not Found, OK vs.
        #std::map<std::string, std::string> _headers : Key value ile header olusturmak icin.
        #std::string _body : body'i tek stringte tutuyoruz.
        #void    addHeader(const std::string &key, const std::string &value)
        #std::string buildHeader() _headers'taki attirbute'lari tek string haline getirir.
        #bool getHeader(const std::string &key, std::string &value)
		#bool getHeaders(const std::string &key, std::vector<std::string> &values)
        #std::string getStatusMessage(HTTPStatusCode statusCode) StatusCode'a uygun message ciktisi verir.
        #std::string getDate() RFC standartlarina gore date formati olusturur.
        #AResponseBase() Private attribute'lari initalize etmeliyiz.
        #void setBody(const td::string &body) Body'i set ettigimiz method.
        +virtual ~AResponseBase()
        +virtual std::string serialize() Response ciktisi alt classta uretilecek
    }

    class IResponse {
        --- Interface ---
        +virtual ~IResponse() Virtual Destructor
        +virtual std::string serialize() Response ciktisi alt classta uretilecek
    }

    class Util {
        void toLowerCase(std::string &str) Tum stringi lowercase yapar.
    }

    class Connection {
	    int _fd : Connection ID
	    std::string _readBuffer : Request class olusana kadar hazir olmayan Requesti tutar.
	    std::string _writeBuffer : generateResponse sonucu olusan IResponse'un serialize'i burada saklanacak. -Her seferinde serialize calisip bellegi yormamasi icin.-
	    RequestBuilder _requestBuilder : RequestBuilder icin nesne olusturuyoruz.
        ResponseFactory _responseFactory : ResponseFactory icin nesne olusturuyoruz.
        ResponseDispatcher _dispatcher : Calistirilabilir dosya yonlendiricisi. Dosya mi? Klasor mu? Yonlendirme.
        Request *_request : Request class olusursa burada saklanacak.
	    IResponse *_response : Response olustugunda burada saklanacak.
	    ConnectionState _state : State machine(READING, WRITING, CLOSING)
	    getFd() Connection ID degerini dondurur.
	    ConnectionState getState() Connection state'i nedir?
	    void addRequest(std::string buffer) Chunked olarak Request'e yani readBuffer'a ekleme yap.
	    void generateResponse() Response uret ve writeBuffer'a yaz
	    void generateRequest() readBuffer'dan Request uretiliyor mu kontrol, uretiliyorsa olustur.
	    bool hasRequest() Request olustu mu?
	    std::string &getResponseBuffer() IResponse ile olusturulmus writ
        eBuffer'i dondurur, writeBuffer degismesi gerekecegi icin referans kullanilir.
	    void resetForNextRequest() Request ve Response degeleri ile bufferlari temizler. State Reading durumuna getirir.
    }

    class ResponseDispatcher {
        --- Su an static calisan dosyalariin var olup olmadigini / klasor mu autoindex yonlenicek mi belirleyen yonlendirici.
        +ResponseDispatcher(ResponseFactory &factory)
        +~ResponseDispatcher()
        +http::IResponse *dispatch(http::Request &request) : Calisan dosyalar icin yonlendirici / response olusturmadan once dosya kontrolu
        -ResponseFactory _factory
    }

    class RequestBuilder {
	    --- BUILDER METHOD DESIGN ---
	    http::ParseState -REQUEST_LINE, HEADERS, BODY, COMPLETE, ERROR-
	    http::ParseStatus -INCOMPLETE, COMPLETE, ERROR-
        http::ParseResult -ParseStatus ve StatusCode saklayan struct-

        -std::string _method;
        -std::string _path;
        -std::string _version;
        -std::vector<std::pair<std::string, std::string> >   _headers;
        -std::string _body;
        -bool    _hasBody;
        -ParseState  _state;
        -ParseResult _parseResult;

	    +http::ParseResult parse(std::string &_readBuffer) : parse private methodlarini sirasiyla calistir.
	    +void reset() : State reset, temizlik
	    +appendBody() : Body parcali gelebilecegi icin append onemli.
        +Request *build() : Requesti olusturur, gecici attribute'lari icine atar ve dondurur.
	    -buildRequestLine(std::string &line) : Ilk satiri parse eder -METHOD PATH VERSION-
	    -buildHeaderLine(std::string &line) : Ilk satir - \r\n\r\n arasi kismi parse eder.
	    -buildBody(std::string &rawReadBuffer) : planlanmadi. su an sadece GET istegi parse ediliyor.
    }

    Connection --> RequestBuilder : makeRequest()
    Connection --> ResponseFactory : makeResponse()
    RequestBuilder --> Request : parse()
    ResponseFactory --> StaticResponse
    ResponseFactory --> ErrorResponse
    ResponseFactory --> AutoIndexResponse
    ResponseFactory --> CGIResponse
    StaticResponse --|> AResponseBase
    ErrorResponse --|> AResponseBase
    AutoIndexResponse --|> AResponseBase
    CGIResponse --|> AResponseBase
    ResponseDispatcher -->IResponse
    AResponseBase --|> IResponse