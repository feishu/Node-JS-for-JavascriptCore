# Node-JS-for-JavascriptCore
Native Node.JS and ECMAScript classes, ported to JavascriptCore. Aim : Run simple Node scripts (server, etc.) by using JavascriptCore.

## What is this?
This is an attempt to write many, many base classes (Which might be in either Objective-C or Swift) of Node.JS, in an attempt to make running a simple server script (or a simple Node shell command) on an iOS device possible.

## Why?
Because we never want to write code twice in different languages, do we?
Write a server/response script once for Node, run a local server on the device, that sort.

## Isn't this a bit too far fetched?
It might be, but I believe in miracles.

# What's here so far?
- EventEmitter

# TODO
- Use [Telegraph](https://github.com/Building42/Telegraph) framework as basis for the HTTP and WebSockets (ws) module
