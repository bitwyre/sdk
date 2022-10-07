import crypto from 'crypto';
import { SignData } from './types';
import { getServerTime } from '@bitwyre-sdk/public';

export async function getNonce(baseUrl: string): Promise<number> {
    const res = await getServerTime(baseUrl);
    return res.data.result.unixtime;
}

export function getChecksum(payload: string): string {
    const temp = JSON.stringify(payload);
    const temp2 = JSON.stringify(temp);
    return crypto.createHash('sha256').update(temp2).digest('hex');
}

export function getNonceChecksum(nonce: string, checksum: string): string {
    return crypto.createHash('sha256').update(nonce.concat(checksum)).digest('hex');
}

export async function sign(baseUrl: string, secretKey: string, uriPath: string, payload: string): Promise<SignData> {
    const nonce: number = await getNonce(baseUrl);
    
    const checksum: string = getChecksum(payload);
    const nonceChecksum = getNonceChecksum(nonce.toString(), checksum);
    const data = uriPath.concat(nonceChecksum);
    const signature = crypto.createHmac('sha512', secretKey)
        .update(data)
        .digest('hex');

    return {
        nonce: nonce,
        checksum: checksum,
        signature: signature,
    }
}