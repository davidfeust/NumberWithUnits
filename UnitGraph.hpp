//
// Created by david on 06/04/2021.
// Thanks to Achiya Zigler for the idea of using this data structure!
//
#pragma once

#include <map>
#include <stack>
#include <bits/stdc++.h>

namespace ariel {

    class UnitGraph {
    private:
        std::map<std::string, std::map<std::string, double>> _graph;
        std::unordered_set<std::string> _nodes;

    public:
        /**
         * Insert edge between to unit nodes.
         * the edge is the conversion unit.
         * @param unit1
         * @param unit2
         * @param conv
         */
        void insert_edge(std::string &unit1, std::string &unit2, double conv) {
            _graph[unit1][unit2] = conv;
            _nodes.insert(unit1);
            _nodes.insert(unit2);
        }

        /**
         * Get the conversion unit of 2 units.
         * this method uses BFS to search on graph.
         * @param unit1
         * @param unit2
         * @return conversion unit
         */
        double get_conv(const std::string &unit1, const std::string &unit2) {
            if (_graph.count(unit1) && _graph[unit1].count(unit2)) {
                return _graph[unit1][unit2];
            }
            std::unordered_set<std::string> visited;
            std::map<std::string, double> conv_ans;
            std::stack<std::string> stack;
            stack.push(unit1);
            conv_ans[unit1] = 1;
            while (!stack.empty()) {
                std::string temp = stack.top();
                stack.pop();
                if (!visited.count(temp)) {
                    visited.insert(temp);
                    if (temp == unit2) {
                        return conv_ans[temp];
                    }
                    for (const auto&[k, v] : _graph[temp]) {
                        if (!visited.count(k)) {
                            conv_ans[k] = v * conv_ans[temp];
                            stack.push(k);
                        }
                    }
                }
            }
            return -1;
        }

        /**
         * Checks if 2 units are in same dim, and if it possible to perform actions on them together.
         * @param unit1
         * @param unit2
         * @return true iff the units in same dim.
         */
        bool is_same_dim(const std::string &unit1, const std::string &unit2) {
            if (_graph[unit1].count(unit2)) {
                return true;
            }
            std::unordered_set<std::string> visited;
            std::stack<std::string> stack;
            stack.push(unit1);
            visited.insert(unit1);
            while (!stack.empty()) {
                std::basic_string<char> &temp = stack.top();
                stack.pop();
                for (const auto&[k, v] : _graph[temp]) {
                    if (k == unit2) {
                        return true;
                    } else if (!visited.count(k)) {
                        visited.insert(k);
                        stack.push(k);
                    }
                }
            }
            return false;
        }

        /**
         * Checks if there exist unit.
         * @param unit
         * @return true iff the unit exist in the graph.
         */
        bool isThereAUnit(const std::string &unit) {
            return _nodes.count(unit);
        }
    };
}