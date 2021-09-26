package com.bitwyre.kotlin_sdk

class Config {
    object baseURL {
        val URL_API_BITWYRE = "https://api.bitwyre.com/"
        val TIMEOUT = 5
        fun getPublicAPIEndpoint(key: String): String? {
            val URI_PUBLIC_API_BITWYRE = HashMap<String, String> ()
            URI_PUBLIC_API_BITWYRE.put("SERVERTIME", "/public/time")
            URI_PUBLIC_API_BITWYRE.put("TRADES", "/public/trades")
            URI_PUBLIC_API_BITWYRE.put("TICKER", "/public/ticker")
            URI_PUBLIC_API_BITWYRE.put("INSTRUMENT", "/public/pairs")
            URI_PUBLIC_API_BITWYRE.put("DEPTH", "/public/depth")
            URI_PUBLIC_API_BITWYRE.put("ANNOUNCEMENTS", "/public/announcements")
            URI_PUBLIC_API_BITWYRE.put("PRODUCTS", "/public/products")
            URI_PUBLIC_API_BITWYRE.put("MARKETS", "/public/markets")
            URI_PUBLIC_API_BITWYRE.put("ASSETS", "/public/assets")
            val value = URI_PUBLIC_API_BITWYRE.get(key)
            return value
        }
        fun getPrivateAPIEndPoint(key: String): String? {
            val URI_PRIVATE_API_BITWYRE = HashMap<String, String> ()
            URI_PRIVATE_API_BITWYRE.put("ACCOUNT_BALANCE", "/private/account/spotbalance")
            URI_PRIVATE_API_BITWYRE.put("ACCOUNT_STATEMENT", "/private/account/statement")
            URI_PRIVATE_API_BITWYRE.put("TRANSACTION_HISTORIES", "/private/account/transactions")
            URI_PRIVATE_API_BITWYRE.put("ORDER", "/private/orders")
            URI_PRIVATE_API_BITWYRE.put("CANCEL_ORDER", "/private/orders/cancel")
            URI_PRIVATE_API_BITWYRE.put("OPEN_ORDERS", "/private/orders/open")
            URI_PRIVATE_API_BITWYRE.put("CLOSED_ORDERS", "/private/orders/closed")
            URI_PRIVATE_API_BITWYRE.put("ORDER_INFO", "/private/orders/info")
            URI_PRIVATE_API_BITWYRE.put("TRADE_HISTORY", "/private/trades")
            val value = URI_PRIVATE_API_BITWYRE.get(key)
            return value
        }
    }
}