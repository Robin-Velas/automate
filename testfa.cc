
#include "gtest/gtest.h"

#include "Automaton.h"

TEST(isValid, handleIsValid) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}


TEST(AddSymbol, AddSymbol_c) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
}

TEST(AddSymbol, AddSymbol_Espilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

TEST(AddSymbol, AddSymbol_non_ascii) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\xc3'));
}


TEST(RemoveSymbol, RemoveSymbol_c) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_TRUE(fa.removeSymbol('c'));
}

TEST(RemoveSymbol, RemoveSymbol_Espilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(fa::Epsilon));
}

TEST(RemoveSymbol, RemoveSymbol_non_ascii) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('\xc3'));
}


TEST(hasSymbol, hasSymbol_c) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_TRUE(fa.hasSymbol('c'));
}

TEST(hasSymbol, hasSymbol_empty) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol(' '));

}

TEST(hasSymbol, hasSymbol_not_valid) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('\xc3'));

}
TEST(hasSymbol, hasSymbol_Espilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol(fa::Epsilon));
}

TEST(hasSymbol, hasSymbol_d_to_e) {
  fa::Automaton fa;
  fa.addSymbol('d');
  EXPECT_FALSE(fa.hasSymbol('e'));
}


TEST(countSymbols, countSymbols_empty) {
  fa::Automaton fa;
  EXPECT_TRUE( 0 == fa.countSymbols());
}

TEST(countSymbols, countSymbols_one) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_TRUE ( 1 == fa.countSymbols());
}



TEST(addState, addState_negative) {
  fa::Automaton fa;
  fa.addState(-1);
  EXPECT_TRUE(fa.countStates() == 0);
}

TEST(addState, addState_1) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.countStates() == 1);
}

TEST(addState, addState_5) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  EXPECT_TRUE(fa.countStates() == 5);
}


TEST(removeState, removeState_1) {
  fa::Automaton fa;
  fa.addState(1);
  fa.removeState(1);
  EXPECT_TRUE(fa.countStates() == 0);
}


TEST(removeState, removeState_1_2) {
  fa::Automaton fa;
  fa.addState(1);
  fa.removeState(2);
  EXPECT_FALSE(fa.countStates() ==0);
}


TEST(removeState, removeState_negative) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(-1));
}
//TODO Remove transitions

TEST(countStates, countStates_one) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.countStates()==1);
}

TEST(countStates, countStates_empty) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.countStates()==0);
}

TEST(countStates, countStates_lot) {
  fa::Automaton fa;
  for(int i = 0; i < 100; i++) {
    fa.addState(i);
  }
  EXPECT_TRUE(fa.countStates() == 100);
}

TEST(setStateInitial, setStateInitial_1_1) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(setStateInitial, setStateInitial_1_2) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(2);
  EXPECT_FALSE(fa.isStateInitial(2));
}

TEST(setStateInitial, setStateInitial_lot) {
  fa::Automaton fa;
  for(int i = 0; i < 10; i++) {
    fa.addState(i);
    fa.setStateInitial(i);
    EXPECT_TRUE(fa.isStateInitial(i));
  }
}

TEST(setStateInitial, setStateInitial_negative) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(-1);
  EXPECT_FALSE(fa.isStateInitial(-1));
}

TEST(setStateFinal, setStateFinal_1_1) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(setStateFinal, setStateFinal_1_2) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(2);
  EXPECT_FALSE(fa.isStateFinal(2));
}

TEST(setStateFinal, setStateFinal_lot) {
  fa::Automaton fa;

  for(int i = 0; i < 10; i++) {
    fa.addState(i);
    fa.setStateFinal(i);
    EXPECT_TRUE(fa.isStateFinal(i));
  }
}

TEST(setStateFinal, setStateFinal_negative) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(-1);
  EXPECT_FALSE(fa.isStateFinal(-1));
}

TEST(addTransition, addTransition_correct){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('c');
  EXPECT_TRUE(fa.addTransition(1, 'c', 2));
}

TEST(addTransition, addTransition_incorrect){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('k');
  EXPECT_FALSE(fa.addTransition(3, 'k', 2));
}
TEST(addTransition, addTransition_not_in_alphabet){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_FALSE(fa.addTransition(1, 'k', 2));
}
TEST(addTransition, addTransition_same_state){
  fa::Automaton fa;
  fa.addState(1);
    fa.addSymbol('k');
  EXPECT_TRUE(fa.addTransition(1, 'k', 1));
}

TEST(addTransition, addTransition_not_ascii){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(3);
    fa.addSymbol('\xc3');
  EXPECT_FALSE(fa.addTransition(1, '\xc3', 3));
}
TEST(removeTransition, removeTransition_correct){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('c');
  fa.addTransition(1, 'c', 2);
  EXPECT_TRUE(fa.removeTransition(1, 'c', 2));
}

TEST(removeTransition, removeTransition_incorrect){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
    fa.addSymbol('k');
  fa.addTransition(3, 'k', 2);
  EXPECT_FALSE(fa.removeTransition(3, 'k', 2));
}

TEST(removeTransition, removeTransition_same_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('k');
  fa.addTransition(1, 'k', 1);
  EXPECT_TRUE(fa.removeTransition(1, 'k', 1));
}

TEST(removeTransition, removeTransition_not_ascii){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(3);
  fa.addSymbol('\xc3');
  fa.addTransition(1, '\xc3', 3);
  EXPECT_FALSE(fa.removeTransition(1, '\xc3', 3));
}

TEST(hasTransition, hasTransition_one) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
    fa.addSymbol('k');
  fa.addTransition(1, 'k', 2);
  EXPECT_TRUE(fa.hasTransition(1, 'k', 2));
}

TEST(hasTransition, hasTransition_a_lot) {
  fa::Automaton fa;
  fa.addState(1); 
  fa.addState(2); 
  fa.addState(3);
  fa.addState(4);

    fa.addSymbol('k');
  for(int i =1, j = 1; i <= 4; i++) {
    fa.addTransition(j, 'k', i);
    EXPECT_TRUE(fa.hasTransition(j, 'k', i));
  }
}

TEST(hasTransition, hasTransition_incorrect) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(3);
    fa.addSymbol('u');
  fa.addTransition(1, 'u', 2);
  EXPECT_FALSE(fa.hasTransition(1,'u',2));
}

TEST(countTransitions, countTransition_empty) {
    fa::Automaton fa;
    EXPECT_TRUE(0 == fa.countTransitions());
}

TEST(countTransitions, countTransition_empty_one_state) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_TRUE(0 == fa.countTransitions());
}

TEST(countTransitions, countTransition_one) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('k');
    fa.addTransition(1, 'k', 2);
    EXPECT_TRUE(1 == fa.countTransitions());
}

TEST(countTransitions, countTransition_) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addSymbol('k');
    fa.addSymbol('h');
    fa.addSymbol('o');
    fa.addSymbol('i');
    fa.addTransition(1, 'k', 2);
    fa.addTransition(1, 'h', 2);
    fa.addTransition(2, 'o', 1);
    fa.addTransition(1, 'o', 3);
    fa.addTransition(2, 'i', 3);
    EXPECT_EQ((size_t)5, fa.countTransitions());
}
/*
TEST(prettyPrint, prettyPrint_) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);

    fa.addSymbol('o');
    fa.addSymbol('k');
    fa.addSymbol('h');
    fa.addSymbol('i');

    fa.setStateFinal(2);
    fa.setStateInitial(1);

    fa.addTransition(1, 'k', 2);
    fa.addTransition(1, 'h', 2);
    fa.addTransition(2, 'o', 1);
    fa.addTransition(1, 'o', 3);
    fa.addTransition(2, 'i', 3);
    fa.prettyPrint(std::cout);
    EXPECT_TRUE(true);
}
*/
TEST(hasEpsilonTransition, empty) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1,'o', 2);
    EXPECT_EQ(0, fa.hasEpsilonTransition());
}

TEST(hasEpsilonTransition, one){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1, fa::Epsilon, 2);
    EXPECT_EQ(1, fa.hasEpsilonTransition());
}


TEST(isDeterministic, empty) {
    fa::Automaton fa;
    EXPECT_TRUE(fa.isDeterministic());
}
TEST(isDeterministic, one) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('p');
    fa.addTransition(1, 'a', 1);
    EXPECT_TRUE(fa.isDeterministic());
}
TEST(isDeterministic, one_complete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
    EXPECT_TRUE(fa.isDeterministic());
}
TEST(isDeterministic, two) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);
    EXPECT_TRUE(fa.isDeterministic());
}
TEST(isDeterministic, two_complete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);

    fa.addSymbol('a');
    fa.addSymbol('b');

    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 2);
    fa.addTransition(2, 'a', 2);
    fa.addTransition(2, 'b', 2);
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(isComplete, one) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('p');
    fa.addTransition(1, 'a', 1);
    EXPECT_FALSE(fa.isComplete());
}
TEST(isComplete, one_complete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
    EXPECT_TRUE(fa.isComplete());
}
TEST(isComplete, two) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);
    EXPECT_FALSE(fa.isComplete());
}
TEST(isComplete, two_complete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);

    fa.addSymbol('a');
    fa.addSymbol('b');

    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 2);
    fa.addTransition(2, 'a', 2);
    fa.addTransition(2, 'b', 2);
    EXPECT_TRUE(fa.isComplete());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
