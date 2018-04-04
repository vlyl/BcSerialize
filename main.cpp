#include <iostream>
#include "transaction.h"
#include "version.h"
#include "streams.h"
#include "utilstrencodings.h"


// Check that all of the input and output scripts of a transaction contains valid opcodes
bool CheckTxScriptsSanity(const CMutableTransaction& tx)
{
    // Check input scripts for non-coinbase txs
    if (!CTransaction(tx).IsCoinBase()) {
        for (unsigned int i = 0; i < tx.vin.size(); i++) {
            if (!tx.vin[i].scriptSig.HasValidOps() || tx.vin[i].scriptSig.size() > MAX_SCRIPT_SIZE) {
                return false;
            }
        }
    }
    // Check output scripts
    for (unsigned int i = 0; i < tx.vout.size(); i++) {
        if (!tx.vout[i].scriptPubKey.HasValidOps() || tx.vout[i].scriptPubKey.size() > MAX_SCRIPT_SIZE) {
            return false;
        }
    }

    return true;
}

bool DecodeHexTx(CMutableTransaction& tx, const std::string& hex_tx, bool try_no_witness, bool try_witness)
{
    if (!IsHex(hex_tx)) {
        return false;
    }

    std::vector<unsigned char> txData(ParseHex(hex_tx));

    if (try_no_witness) {
        CDataStream ssData(txData, SER_NETWORK, PROTOCOL_VERSION | SERIALIZE_TRANSACTION_NO_WITNESS);
        try {
            ssData >> tx;
            if (ssData.eof() && (!try_witness || CheckTxScriptsSanity(tx))) {
                return true;
            }
        } catch (const std::exception&) {
            // Fall through.
        }
    }

    if (try_witness) {
        CDataStream ssData(txData, SER_NETWORK, PROTOCOL_VERSION);
        try {
            ssData >> tx;
            if (ssData.empty()) {
                return true;
            }
        } catch (const std::exception&) {
            // Fall through.
        }
    }

    return false;
}


int main() {
    const std::string data = "02000000064bc7ee6647910c47ae5e400d3c0cfb6c1f8dce6378b6459d908393e3e16d15f70000000000feffffff9a93dbaa10567899c6d8adaf14245074023e5856103e5fa7e64918966bd401630000000000feffffffbc94ff6061352469ae2a194e919afd2d041a3bf47bd39519cb4e151c234cd4a80000000000feffffffc2a7d416e2408a80ac909675d1690abc79ada67921abe169cf5e9d04c421dd480000000000feffffffd12a7a129d32514bc86ce5f1ef8bd68cc80e117ca6c8454fb2c91af3368b46d60000000000feffffffe42f204825ff58f64d407409935d90a6d30773367aa3fcc51f2d6ded8d70e8d00000000000feffffff0200ca9a3b0000000017a914eaf999a752ea5a289020a8ccc5c6f0546cb710088785ff10000000000017a91455ad7dab1cdb8792b6ef77eac4050f8f5d11e9048700000000";
    CMutableTransaction mtx;
    DecodeHexTx(mtx, data, false, true);
    auto tx = CTransaction(std::move(mtx));
    return 0;
}