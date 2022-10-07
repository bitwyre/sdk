import { getAccountBalance } from '..';
import * as dotenv from 'dotenv';

dotenv.config({ path: `${__dirname}/../.env` });

async function main() {
  const res = await getAccountBalance(
    `https://api.bitwyre.com`,
    process.env.API_KEY ?? '',
    process.env.SECRET_KEY ?? '',
  );
  return res.data;
}

main()
  .then(console.log)
  .catch((e) => console.log(e.response.data));
