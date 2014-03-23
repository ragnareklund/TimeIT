#ifndef MOCKNETWORK_H_
#define MOCKNETWORK_H_

#include "Network.h"

#include <map>

namespace Test
{

class MockNetwork: public INetwork
{
public:
	MockNetwork();
	virtual ~MockNetwork();
	virtual std::string request(const std::string& url, std::string data, std::string username, std::string password);
	void setResponse(std::string& uri, std::string& response);
private:
	std::map<std::string, std::string> responses;
};

} /* namespace Test */
#endif /* MOCKNETWORK_H_ */
