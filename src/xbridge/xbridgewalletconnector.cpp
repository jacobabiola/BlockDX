//*****************************************************************************
//*****************************************************************************

#include "xbridgewalletconnector.h"
#include "xbridgetransactiondescr.h"

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
namespace wallet
{

//*****************************************************************************
//*****************************************************************************
std::string UtxoEntry::toString() const
{
    std::ostringstream o;
    o << txId << ":" << vout << ":" << amount << ":" << address;
}

//*****************************************************************************
//*****************************************************************************
bool operator < (const UtxoEntry & l, const UtxoEntry & r)
{
    return (l.txId < r.txId) || (l.vout < r.vout);
}

//*****************************************************************************
//*****************************************************************************
bool operator == (const UtxoEntry & l, const UtxoEntry & r)
{
    return (l.txId == r.txId) && (l.vout == r.vout);
}

} // namespace wallet

//*****************************************************************************
//*****************************************************************************
WalletConnector::WalletConnector()
{

}

//******************************************************************************
//******************************************************************************
double WalletConnector::getWalletBalance() const
{
    std::vector<wallet::UtxoEntry> entries;
    if (!getUnspent(entries))
    {
        LOG() << "getUnspent failed " << __FUNCTION__;
        return 0;
    }

    double amount = 0;
    for (const wallet::UtxoEntry & entry : entries)
    {
        amount += entry.amount;
    }

    return amount;
}

} // namespace xbridge
