/*
 * gnote
 *
 * Copyright (C) 2012 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */




#include <libxml/xpath.h>

#include "sharp/xml.hpp"


namespace sharp {

  XmlNodeSet xml_node_xpath_find(const xmlNodePtr node, 
                                 const char * xpath)
  {
    XmlNodeSet nodes;

    if(!node) {
      return nodes;
    }
    xmlXPathContext* ctxt = xmlXPathNewContext(node->doc);
    ctxt->node = node;

    xmlXPathObject* result = xmlXPathEval((const xmlChar*)xpath, ctxt);

    if(result && (result->type == XPATH_NODESET)) {
      xmlNodeSetPtr nodeset = result->nodesetval;

      if(nodeset)
      {
        nodes.reserve(nodeset->nodeNr);
        for (int i = 0; i != nodeset->nodeNr; ++i) {
          nodes.push_back(nodeset->nodeTab[i]);
        }
      }
    }

    if(result) {
      xmlXPathFreeObject(result);
    }
    if(ctxt) {
      xmlXPathFreeContext(ctxt);
    }

    return nodes;
  }


  std::string xml_node_xpath_find_single(const xmlNodePtr node,
                                         const char * xpath)
  {
    xmlNodePtr n = xml_node_xpath_find_single_node(node, xpath);
    if(!n) {
      return "";
    }

    char *res = reinterpret_cast<char*>(XML_GET_CONTENT(n));
    return res ? res : "";
  }


  xmlNodePtr xml_node_xpath_find_single_node(const xmlNodePtr node,
                                             const char * xpath)
  {
    xmlXPathContext* ctxt = xmlXPathNewContext(node->doc);
    ctxt->node = node;

    xmlXPathObject* result = xmlXPathEval((const xmlChar*)xpath, ctxt);

    xmlNodePtr result_node = NULL;
    if(result && (result->type == XPATH_NODESET)) {
      xmlNodeSetPtr nodeset = result->nodesetval;

      if(nodeset && nodeset->nodeNr) {
          result_node = nodeset->nodeTab[0];
      }
    }

    if(result) {
      xmlXPathFreeObject(result);
    }
    if(ctxt) {
      xmlXPathFreeContext(ctxt);
    }

    return result_node;
  }


  std::string xml_node_content(xmlNodePtr node)
  {
    if(!node) {
      return "";
    }
    if(node->type == XML_ATTRIBUTE_NODE) {
      node = xmlGetLastChild(node);
      if(!node) {
	return "";
      }
    }
    char *res = reinterpret_cast<char*>(XML_GET_CONTENT(node));
    return res ? res : "";
  }


  std::string xml_node_get_attribute(const xmlNodePtr node,
                                     const char * attr_name)
  {
    char *res = reinterpret_cast<char*>(xmlGetProp(node, reinterpret_cast<const xmlChar*>(attr_name)));
    return res ? res : "";
  }

}
