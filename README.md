<p align="center">
  <a href="https://github.com/bitwyre">
    <img src="https://github.com/bitwyre/interface/blob/develop/public/static/images/logo.png" alt="Logo" height="80" width="auto">
  </a>
</p>

# Bitwyre's Software Development Kit 

Algorithmic trading development on Bitwyre's crypto spot and derivative exchange.

# Getting Started

## What is SDK?

Here, a software development kit (aka `SDK`) refers to a set of tools, guidelines
and programs used to develop application for our algorithmic trading platform.
Our SDK includes APIs to a variety of programming languages, documentation, libraries, code samples
and other utilities. Our SDK boast a set of robust features and functionalities by wrapping
all the complexity calling an API directly into specific programming languages users consider.

## What is a REST API?
Roughly speaking, a REST API is about getting request and processing response.

The Dispatcher class is responsible to send request. Each end point has to process response, write it to JSON format output.

The API URL is retrieved from the environment variable `URL_API_BITWYRE`, but if you do not set it, a default one
pointing to our production cluster will be used.

## Gateways

Bitwyre electronic trading team developed several interfaces to trade on our exchange

- REST (HTTP + JSON) gateway
- Websocket gateway
- Financial Information Exchange (FIX) gateway

## Programming Languages

We also have included basic trading bots in several popular programming languages

- Python
- C++
- Rust
- Objective-C
- Kotlin
- Java
- Scala
- Swift
- Javascript

# Copyright

2021, Bitwyre Technologies Holdings Incorporated
