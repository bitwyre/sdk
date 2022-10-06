import axios from 'axios';
import { sign, SignData } from './authentication';

export async function spotBalance(baseUrl: string, apiKey: string, secretKey: string, page?: number, perPage?: number, usePagination: boolean = false, asset: string  = "") {
    const payload = "";
    const uriPath: string = "/private/account/spotbalance";
    const signData: SignData = await sign(secretKey, uriPath, payload);
    
    return await axios.get(uriPath, {
        baseURL: baseUrl,
        params: {
            "nonce": signData.nonce,
            "checksum": signData.checksum,
            "payload": payload
        },
        headers: {
            "API-Key": apiKey,
            "API-Sign": signData.signature
        }
    });
}