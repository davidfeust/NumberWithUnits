//
// Created by david on 06/04/2021.
//
#pragma once

#include <map>
#include <stack>
#include <bits/stdc++.h>

namespace ariel {

    class Unit {
    private:
        std::map<std::string, std::map<std::string, double>> graph;
        std::unordered_set<std::string> nodes;

    public:
        void insert_edge(std::string &unit1, std::string &unit2, double conv) {
            graph[unit1][unit2] = conv;
            nodes.insert(unit1);
            nodes.insert(unit2);
        }

        double get_conv(const std::string &unit1, const std::string &unit2) {
            if (graph.contains(unit1) && graph[unit1].contains(unit2)) {
                return graph[unit1][unit2];
            }
            double ans = 1;
            std::unordered_set<std::string> visited;
            std::stack<std::string> stack;
            stack.push(unit1);
            visited.insert(unit1);
            while (!stack.empty()) {
                std::basic_string<char> &temp = stack.top();
                stack.pop();
                for (const auto&[k, v] : graph[temp]) {
                    if (k == unit2) {
                        return ans * v;
                    }
                    if (!visited.contains(k)) {
                        visited.insert(k);
                        stack.push(k);
                        ans *= v;
                    }
                }
            }
            return ans;
        }

        bool is_same_dim(const std::string &unit1, const std::string &unit2) {
            if (graph[unit1].contains(unit2)) {
                return true;
            }
            std::unordered_set<std::string> visited;
            std::stack<std::string> stack;
            stack.push(unit1);
            visited.insert(unit1);
            while (!stack.empty()) {
                std::basic_string<char> &temp = stack.top();
                stack.pop();
                for (const auto&[k, v] : graph[temp]) {
                    if (k == unit2) {
                        return true;
                    } else if (!visited.contains(k)) {
                        visited.insert(k);
                        stack.push(k);
                    }
                }
            }
            return false;
        }

        bool isThereAUnit(const std::string& unit) {
            return nodes.contains(unit);
        }
    };


}