# Kindle Web Wrapper

An unofficial Linux desktop wrapper for Amazon Kindle for Web, built with GTK4 and WebKitGTK.

## Description

This application wraps the [Amazon Kindle for Web](https://read.amazon.com/) reader in a native Linux desktop window using WebKitGTK. It provides a standalone desktop experience for reading your Kindle books without needing a browser.

## Features

- Native GTK4 desktop application
- Persistent login and session data
- Cookie persistence across sessions
- Window size: 1280x850 (default)

## Dependencies

- GTK4
- WebKitGTK 6.0
- pkg-config

## Building

### Build with Flatpak

```bash
flatpak-builder --user --install --force-clean build-dir com.github.kindleweb.Kindle.yml
```

### Build manually

```bash
gcc -O2 -Wall -Wextra -o kindle-web src/main.c $(pkg-config --cflags --libs gtk4 webkitgtk-6.0)
```

## Running

### Run Flatpak

```bash
flatpak run com.github.kindleweb.Kindle
```

### Run manually

```bash
./kindle-web
```

## License

MIT
=======
## License

MIT
=======
# 012_flatpak_for_AmazonKindle
Electron web wrapper in form of Flatpak for Amazon Kindle.
