/*
Copyright 2015 cyclical.state@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.





*/
#include <libipc\libipc.h>


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