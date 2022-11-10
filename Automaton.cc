#include "Automaton.h"

namespace fa {

    Automaton::Automaton() {

    }

    bool Automaton::isValid() const {
        if ((alphabet.empty()) || (allStates.empty())) {
            return false;
        }
        return true;
    }

    bool Automaton::addSymbol(char symbol) {
        if (symbol == Epsilon) {
            return false;
        }
        if (isgraph(symbol) == 0) {
            return false;
        }

        alphabet.push_back(symbol);
        return true;
    }

    bool Automaton::removeSymbol(char symbol) {

        if (symbol == Epsilon) {
            return false;
        }
        if (isgraph(symbol) == 0) {
            return false;
        }

        for (size_t i = 0; i < alphabet.size(); ++i) {
            if (alphabet[i] == symbol) {
                alphabet.erase(alphabet.begin() + i);
                return true;
            }
        }
        //the symbol is correct but isn't in the alphabet

        return false;

    }

    bool Automaton::hasSymbol(char symbol) const {

        if (symbol == Epsilon) {
            return false;
        }
        if (isgraph(symbol) == 0) {
            return false;
        }

        for (size_t i = 0; i < alphabet.size(); ++i) {
            if (alphabet[i] == symbol) {
                return true;
            }
        }
        return false;
    }

    std::size_t Automaton::countSymbols() const {
        return (size_t) alphabet.size();
    }

    bool Automaton::addState(int state) {

        if ((state < 0)) {
            return false;
        }
        struct aut_state temp;

        temp.isInitial = false;
        temp.isFinal = false;
        temp.transitions = {};

        allStates.insert({state, temp});

        return true;

    }

    bool Automaton::removeState(int state) {

        if ((state < 0)) {
            return false;
        }
        //delete all transitions to this state
        for (const auto &etat: allStates) {
            for (const auto &transition: etat.second.transitions) {
                if (transition.second.find(state) != transition.second.end()) {
                    transition.second.erase(state);
                }
            }
        }
        allStates.erase(state);
        return true;

    }

    bool Automaton::hasState(int state) const {
        if ((state < 0)) {
            return false;
        }
        if (allStates.find(state) == allStates.end())
            return false;

        return true;
    }

    std::size_t Automaton::countStates() const {
        return (size_t) allStates.size();
    }

    void Automaton::setStateInitial(int state) {
        if ((state < 0)) {
            return;
        }

        //does it work when state is not relied with a value ?
        auto p = allStates.find(state);
        if (p == allStates.end()) {
            return;
        }
        allStates[state].isInitial = true;

    }

    bool Automaton::isStateInitial(int state) const {
        if ((state < 0)) {
            return false;
        }
        auto p = allStates.find(state);
        if (p == allStates.end()) {
            return false;
        }
        return allStates.find(state)->second.isInitial;
    }

    void Automaton::setStateFinal(int state) {
        if ((state < 0)) {
            return;
        }
        auto p = allStates.find(state);
        if (p == allStates.end()) {
            return;
        }
        allStates[state].isFinal = true;
    }

    bool Automaton::isStateFinal(int state) const {
        if ((state < 0)) {
            return false;
        }
        auto p = allStates.find(state);
        if (p == allStates.end()) {
            return false;
        }
        return allStates.find(state)->second.isFinal;
    }

    bool Automaton::addTransition(int from, char alph, int to) {
        if (alph!= Epsilon) {
            bool isInAlphabet = false;
            for (char i: alphabet) {
                if (i == alph)
                    isInAlphabet = true;
            }
            if (!isInAlphabet) {
                return false;
            }
        }
        if ((isgraph(alph) == 0) && (alph != Epsilon)) {
            return false;
        }
        if ((allStates.find(from) == allStates.end()) || (allStates.find(to) == allStates.end())) {
            return false;
        }

        auto p = allStates[from].transitions[alph].insert(to);

        if (!p.second) {
            return false;
        }
        return true;
    }

    bool Automaton::removeTransition(int from, char alph, int to) {
        if (alph!= Epsilon) {
            bool isInAlphabet = false;
            for (char i: alphabet) {
                if (i == alph)
                    isInAlphabet = true;
            }
            if (!isInAlphabet) {
                return false;
            }
        }
        if ((isgraph(alph) == 0) || (alph == Epsilon)) {
            return false;
        }
        auto p = allStates[from].transitions.find(alph);
        if (p == allStates[from].transitions.end())
            return false;

        allStates[from].transitions[alph].erase(to);
        return true;
    }

    bool Automaton::hasTransition(int from, char alph, int to) const {

        if (alph!= Epsilon) {
            bool isInAlphabet = false;
            for (char i: alphabet) {
                if (i == alph)
                    isInAlphabet = true;
            }
            if (!isInAlphabet) {
                return false;
            }
        }
        if ((isgraph(alph) == 0) || (alph == Epsilon)) {
            return false;
        }
        auto p = allStates.find(from);
        if (p == allStates.end())
            return false;

        auto k = p->second.transitions.find(alph);
        if (k == p->second.transitions.end())
            return false;

        auto z = k->second.find(to);
        if (z == k->second.end())
            return false;

        return true;

    }

    std::size_t Automaton::countTransitions() const {
        size_t count = 0;
        for (const auto &etat: allStates) {
            for (const auto &transition: etat.second.transitions) {
                count += transition.second.size();
            }
        }
        return count;
    }

    void Automaton::prettyPrint(std::ostream &os) const {
        //AFFICHAGE ETATS INITIAUX / FINAUX
        std::string init, final;
        for (const auto &etat: allStates) {

            if (etat.second.isFinal)
                init += " " + std::to_string(etat.first);

            if (etat.second.isInitial)
                final += " " + std::to_string(etat.first);
        }
        os << "Etat(s) initiale(s) : " << init << std::endl;
        os << "Etat(s) final( / finaux) : " << final << std::endl;
        os << std::endl;

        //AFFICHAGE TRANSITIONS
        os << "Transitions : " << std::endl;
        for (const auto &etat: allStates) {
            os << "    For state " << etat.first << ":" << std::endl;
            for (const auto &transition: etat.second.transitions) {
                os << "        For letter " << transition.first << " : ";
                for (int iter: transition.second) {
                    os << iter;
                }
                os << std::endl;
            }
            os << std::endl;
        }
    }

    bool Automaton::hasEpsilonTransition() const {

        for (auto &etat: allStates) {
            if (etat.second.transitions.find(Epsilon) != etat.second.transitions.end()) {
                return true;
            }
        }
        return false;
    }
    bool Automaton::isDeterministic() const {

        for (auto &etat: allStates) {
            for(auto &transi : etat.second.transitions) {
                if (transi.second.size() > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Automaton::isComplete() const {

        for (auto &etat: allStates) {
            for (auto &letter: alphabet) {

                auto ret = etat.second.transitions.find(letter);
                if (ret == etat.second.transitions.end())
                    return false;
            }
        }
        return true;
    }
}

