#ifndef __HEADER_DFA__
#define __HEADER_DFA__

#include "../util/GeneralUtil.h"
#include "../util/RegexUtil.h"
#include <memory>

namespace TBox {
    namespace Lexan {
        namespace DFA {
            class CharSet {
                short char_set[65536];
                short id[65536];
                int id_;
            public:
                CharSet();
                void merge(wch ch1, wch ch2);
                void giveID(wch ch1);
                short find(wch ch);
                short toID(short set);
            };
            class DFA {
                short sets_num;
                short states;
                short** transform_matrix;
                std::vector<short> end_states;
                short cur_state;
                const short start_state;
                CharSet& charset;
            public:
                DFA(short sets_num, short states, short start_stateIn, CharSet& charsetIn, std::vector<short> end_states);
                ~DFA();
                void addTranform(short from, short to, short set);
                short getTransform(short from, short set);
                void doTransform(short set);
                int run(std::wstring program);
            };
            struct TransformEdge {
                short from;
                short to;
                std::initializer_list<short> set;
            };
            class DFABuilder {
                std::vector<TransformEdge> transforms;
                std::vector<short> end_states;
            public:
                DFABuilder();
                void addTranform(short from, short to, std::initializer_list<short> set);
                void addEndState(short state);
                DFA* build();
            };
            void addTransformFromRegexNode(DFABuilder& dfa, Util::Regex::ASTNode* regex_node);
        }
    }
}

#endif