import { spotBalance } from "../spot";

async function main () {
    try{
        const res = await spotBalance(
            `https://api.bitwyre.com`,
            '',
            '',
        );
        return res.data;
    }
    catch(e: any) {
        console.log(e.response.data);
    }
}

main()
    .then();