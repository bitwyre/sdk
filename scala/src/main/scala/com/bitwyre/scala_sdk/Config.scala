package com.bitwyre.scala_sdk

import scala.collection.mutable.HashMap

class Config {
    object baseURL {
        val URL_API_BITWYRE: String = "https://api.bitwyre.com/"
        val TIMEOUT: Int = 5
        def getPublicAPIEndpoint(key: String): String = {
            val URI_PUBLIC_API_BITWYRE = HashMap(
                "SERVERTIME" -> "/public/time",
                "TRADES" -> "/public/trades",
                "TICKER" -> "/public/ticker",
                "INSTRUMENT" -> "/public/pairs",
                "DEPTH" -> "/public/depth",
                "ANNOUNCEMENTS" -> "/public/announcements",
                "PRODUCTS" -> "/public/products",
                "MARKETS" -> "/public/markets",
                "ASSETS" -> "/public/assets"
            )
            URI_PUBLIC_API_BITWYRE(key)
        }
        def getPrivateAPIEndPoint(key: String): String = {
            val URI_PRIVATE_API_BITWYRE = HashMap(
                "ACCOUNT_BALANCE" -> "/private/account/spotbalance",
                "ACCOUNT_STATEMENT" -> "/private/account/statement",
                "TRANSACTION_HISTORIES" -> "/private/account/transactions",
                "ORDER" -> "/private/orders",
                "CANCEL_ORDER" -> "/private/orders/cancel",
                "OPEN_ORDERS" -> "/private/orders/open",
                "CLOSED_ORDERS" -> "/private/orders/closed",
                "ORDER_INFO" -> "/private/orders/info",
                "TRADE_HISTORY" -> "/private/trades"
            )
            URI_PRIVATE_API_BITWYRE(key)
        }
    }
}
