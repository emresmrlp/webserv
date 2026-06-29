*This project has been created as part of the 42 curriculum by ysumeral, beldemir.*

# webserv

A simple HTTP/1.1 server written in C++98. It does not block operations (non-blocking) and uses a configuration file that looks like NGINX.

## Description

**webserv** is a 42 School project. Our goal was to write our own HTTP server from scratch. We didn't use any external HTTP libraries. It follows the HTTP/1.1 rules It can share static files, accept file uploads, and run CGI scripts (like Python or PHP).

We organized our code into different folders to keep it clean:
- **`config/`** — Tokenizes and parses the configuration file into immutable `ConfigServer` / `ConfigLocation` objects (built via the Builder pattern).
- **`core/`** — Runs the server loop using poll(). It handles all connections without stopping other operations.
- **`http/request/`** — Incrementally parses raw TCP bytes into a `Request` object, supporting both `Content-Length` and chunked transfer encoding.
- **`http/handler/`** — One handler per HTTP method (`GET`, `POST`, `PUT`, `DELETE`, `HEAD`, CGI) implementing the Strategy pattern behind a common `IMethodHandler` interface.
- **`http/response/`** — Builds and serializes HTTP responses (static files, redirects, autoindex, error pages, CGI output) behind a common `IResponse` interface.

### Key features

- Multiple `listen` directives per server
- Static file serving with custom `index`, `autoindex` (directory listing), and custom error pages
- Supports `GET`, `HEAD`, `POST`, `PUT` and `DELETE`
- File upload support
- Can run CGI scripts (like Python and PHP).
- Chunked transfer encoding (request side)
- Configurable connection body/header size limits and HTTP redirections

## Instructions

### Requirements

- A C++98-compatible compiler
- `make`

### Compilation

```bash
cd webserv
make
```

This produces a `webserv` binary at the project root. Other available targets:

```bash
make clean   # remove object files
make fclean  # remove object files and the binary
make re      # fclean + all
```

### Running the server

```bash
./webserv <path-to-config-file>
```

Sample configuration files are provided in the [`conf/`](./conf) directory. For example:

```bash
./webserv conf/default.conf
```

Once running, the server can be reached with any HTTP client, for instance:

```bash
curl http://localhost:<port>/
```

### Configuration file syntax (overview)
```
server {
    listen 127.0.0.1:8080;
    listen 127.0.0.1:8081;
    listen 127.0.0.1:8082;
    root www;
    server_name localhost 127.0.0.1;
    client_max_body_size 10m;
    location /
    {
        root www;
        allowed_methods GET;
        autoindex on;
        index index.html;
        cgi_pass .bla ./cgi_tester;
        cgi_pass .py /usr/bin/python3;
    }
    location /post_body
    {
        client_max_body_size 100;
        root www;
        allowed_methods POST;
        cgi_pass .bla ./cgi_tester;
        cgi_pass .py /usr/bin/python3;
    }
    location /directory/
    {
        root YoupiBanane;
        allowed_methods GET;
        autoindex off;
        index youpi.bad_extension;
        cgi_pass .bla ./cgi_tester;
        cgi_pass .py /usr/bin/python3;
    }
}
```

## Resources

### References

- [RFC 9110 — HTTP Semantics](https://www.rfc-editor.org/rfc/rfc9110)
- [RFC 9112 — HTTP/1.1](https://www.rfc-editor.org/rfc/rfc9112)
- [RFC 3875 — The Common Gateway Interface (CGI) Version 1.1](https://www.rfc-editor.org/rfc/rfc3875)
- [MDN — HTTP Overview](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [`poll(2)` man page](https://man7.org/linux/man-pages/man2/poll.2.html)
- [Design Patterns (refactoring.guru)](https://refactoring.guru/design-patterns)
- [Mermaid JS For Architecture](https://mermaid.js.org/)
- [NGINX Documentation](https://nginx.org/en/docs/) (used as a reference for the configuration file style)

### AI Usage

- **Design Pattern Guidance** — To learn how to organize our code better using patterns (like Builder, Strategy, and Factory) before we started writing it.
- **Debugging** — To find and fix hard problems. For example, fixing connection errors in our server loop, reading data that comes in pieces (chunked data), and making sure CGI scripts get the right information.
- **Documentation** — To help us write this README file.
- **GitHub Actions** — To create automatic tests that check our code every time we upload it to GitHub.

