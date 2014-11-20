#include <libipc.h>


namespace libipc
{
	std::unique_ptr<IpcDomain> root_domain_fs;
    std::unique_ptr<IpcSymbolTable> root_symbol_table;

	static int InitializeLibIpc
	(
	 unsigned domain_depth = max_domain_depth, 
	 unsigned domain_links = max_domain_links,
	 unsigned unique_interfaces = max_unique_interfaces,
	 unsigned subs_per_port = max_subscr_length
	)
	{
		if (root_domain_fs) { return; }

		max_subscr_length = subs_per_port;
		max_unique_interfaces = unique_interfaces;
		max_domain_links = domain_links;
		max_domain_depth = domain_depth;


		root_symbol_table = 
			std::make_unique<IpcSymbolTable>
			(new IpcSymbolTable(max_domain_links*max_domain_depth,
			max_domain_links*max_domain_depth*max_port_per_domain));
	}
}