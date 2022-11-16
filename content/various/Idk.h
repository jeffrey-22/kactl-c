/**
 * Author: AA
 * Date: 2015-03-18
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: I don't know why this is here.
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using ordered_set = tree < int ,  null_type ,  less ,  rb_tree_tag ,  tree_order_statistics_node_update >;

#define dbg(...) u_u(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void u_u(string vars, Args&&... values){
    cout << "[" << vars << "] -> ";
    ((cout << "[" << values << "]"), ...);
    cout << "\n";
}