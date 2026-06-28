*This project has been created as part of the 42 curriculum by ysumeral, beldemir.*

# webserv

A non-blocking, event-driven HTTP/1.1 server written from scratch in C++98, inspired by NGINX's configuration philosophy.

## Description

**webserv** is a 42 School project whose goal is to implement an HTTP server compliant enough with the HTTP/1.1 protocol (RFC 9112) to serve static files, handle file uploads, and execute CGI scripts, all without relying on any external HTTP library.

The server is configured through a single NGINX-style configuration file describing one or more virtual servers, each with its own listen address(es), routes (`location` blocks), error pages, body/header size limits, and CGI bindings. Internally, the project is split into clearly separated layers, each with a single responsibility:

- **`config/`** — Tokenizes and parses the configuration file into immutable `ConfigServer` / `ConfigLocation` objects (built via the Builder pattern).
- **`core/`** — Owns the `poll()`-based event loop, socket lifecycle, and per-connection state machine (non-blocking I/O only, single-threaded).
- **`http/request/`** — Incrementally parses raw TCP bytes into a `Request` object, supporting both `Content-Length` and chunked transfer encoding.
- **`http/handler/`** — One handler per HTTP method (`GET`, `POST`, `PUT`, `DELETE`, `HEAD`, CGI) implementing the Strategy pattern behind a common `IMethodHandler` interface.
- **`http/response/`** — Builds and serializes HTTP responses (static files, redirects, autoindex, error pages, CGI output) behind a common `IResponse` interface.

### Key features

- Multiple virtual servers and multiple `listen` directives per server
- Static file serving with custom `index`, `autoindex` (directory listing), and custom error pages
- `GET`, `HEAD`, `POST`, `PUT`, `DELETE` methods, restrictable per route
- File upload support
- CGI execution (e.g. Python, PHP) with proper `SCRIPT_NAME` / `PATH_INFO` / `QUERY_STRING` environment setup (RFC 3875)
- Chunked transfer encoding (request side)
- Keep-alive connections
- Configurable client body/header size limits and HTTP redirections per route

## Instructions

### Requirements

- A C++98-compatible compiler (`c++`/`g++`/`clang++`)
- `make`
- Linux (the project is developed and tested primarily on the 42 cluster / x86 Linux; behavior on other UNIX-like systems is not guaranteed)

### Compilation

```bash
git clone https://github.com/emresmrlp/webserv.git
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

If no configuration file is given, the server falls back to a default configuration.

Once running, the server can be reached with any HTTP client, for instance:

```bash
curl http://localhost:<port>/
```

or simply by visiting `http://localhost:<port>/` in a browser. Static assets served by default are located under [`www/`](./www) and [`www2/`](./www2).

### Configuration file syntax (overview)

The configuration format loosely follows NGINX conventions:

```nginx
server {
    listen 8080;
    server_name example.local;
    root www;
    index index.html;

    location / {
        allow_methods GET POST;
        autoindex on;
    }

    location /upload {
        allow_methods POST DELETE;
        upload_path www/uploads;
    }

    location /cgi-bin {
        cgi_pass .py /usr/bin/python3;
    }

    error_page 404 /errors/404.html;
}
```

See [`conf/`](./conf) for complete, working examples.

### Testing

Two test binaries are provided at the project root:

- `tester` — general HTTP conformance tests
- `cgi_tester` — CGI-specific tests

```bash
./tester
./cgi_tester
```

> Note: these test binaries are built for x86 Linux; they may not run on ARM-based machines (e.g. Apple Silicon) without an x86 emulation layer (such as UTM).

Continuous integration (build checks via GitHub Actions) is configured under [`.github/workflows`](./.github/workflows).

## Resources

### Protocol & standards references

- [RFC 9110 — HTTP Semantics](https://www.rfc-editor.org/rfc/rfc9110)
- [RFC 9112 — HTTP/1.1](https://www.rfc-editor.org/rfc/rfc9112)
- [RFC 3875 — The Common Gateway Interface (CGI) Version 1.1](https://www.rfc-editor.org/rfc/rfc3875)
- [MDN — HTTP Overview](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [`poll(2)` man page](https://man7.org/linux/man-pages/man2/poll.2.html)
- [NGINX documentation](https://nginx.org/en/docs/) (used as a reference for the configuration file philosophy)

### AI usage

AI (Claude, Anthropic) was used as a support and learning tool throughout the project, specifically for:

- **Design pattern guidance** — discussing and validating the use of the Builder pattern (`ConfigServerBuilder` / `ConfigLocationBuilder`), the Strategy pattern (`IMethodHandler` and its concrete handlers), and the Factory pattern (`ResponseFactory`) before implementation.
- **Debugging** — investigating and resolving issues such as file descriptor leaks and double-close bugs in the `poll()` event loop, index invalidation during connection removal, chunked transfer-encoding parsing edge cases, and CGI environment variable construction (`SCRIPT_NAME`, `PATH_INFO`, `QUERY_STRING`).
- **Documentation** — drafting the architecture overview (layer breakdown, design pattern usage, request lifecycle) summarized in this README, based on the project's actual source and header files.
- **GitHub Actions** — drafting and adjusting the CI workflow configuration under [`.github/workflows`](./.github/workflows).

All AI-assisted code, explanations, and suggestions were reviewed, tested, and adapted by the team before being integrated into the project. No code was used without understanding it.
