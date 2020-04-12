//
// Created by pikachu on 2020/4/11.
//
#include "common.h"
#include "symbol.h"
string procedure_symbol::to_string() const {
    std::string param_string;
    if (params.empty()) {
        param_string += "[]";
    } else {
        param_string += "[";
        for(int i=0;i<params.size()-1;i++) {
            param_string += fmt::format("{}, ", params[i]->to_string());
        }
        param_string += params.back()->to_string();
        param_string += "]";
    }
    return fmt::format("<ProcedureSymbol(name={}, parameters={})>", name, param_string);
}

scoped_symbol_table::scoped_symbol_table(string name, scoped_symbol_table *scope)
        : scope_name(std::move(name)), enclosing_scope(scope) {
    spdlog::info("ENTER scope: {}", scope_name);
    if (scope) {
        scope_level = scope->scope_level + 1;
    }
}

void scoped_symbol_table::define(symbol *symbol) {
    spdlog::info("Define: {}", symbol->to_string());
    symbols[symbol->name] = symbol;
}

void scoped_symbol_table::insert(symbol *symbol) {
    spdlog::info("Insert: {}", symbol->name);
    symbols[symbol->name] = symbol;
}

symbol *scoped_symbol_table::lookup(const string &name) {
    spdlog::info("Lookup: {}. (Scope name: {})", name, scope_name);
    if (symbols.find(name) == symbols.end()) {
        if (enclosing_scope) return enclosing_scope->lookup(name);

        SPDLOG_ERROR("Unknown type {}", name);
        exit(1);
    }
    return symbols[name];
}

std::string scoped_symbol_table::to_string() {
    std::string ret;
    ret += "Symbols: "s;
    ret += "["s;
    for(auto [k, v] : symbols) {
        ret += v->to_string();
        ret += ", ";
    }
    ret += "]"s;
    return ret;
}

std::string scoped_symbol_table::to_table_string() {
    std::string ret;
    std::string header = "SCOPE (SCOPED SYMBOL TABLE)"s;
    ret += header;
    ret += "\n"s;
    ret += string(header.size(), '=');
    ret += "\n"s;
    ret += fmt::format("Scope name     : {}\n", scope_name);
    ret += fmt::format("Scope level    : {}\n", scope_level);
    ret += fmt::format("Enclosing scope: {}\n", enclosing_scope ? enclosing_scope->scope_name : "None"s);
    std::string content_header = "Scope (Scoped symbol table) contents";
    ret += content_header;
    ret += "\n"s;
    ret += string(content_header.size(), '-');
    ret += "\n"s;
    for(auto [k, v]: symbols) {
        ret += fmt::format("{:>7}: {}\n", k, v->to_string());
    }
    return ret;
}