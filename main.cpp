#include "project_CTRR.cpp"

int main()
{
    //49*(41*39)-(145+78)+193+(121*135+101-88)
    cout << Infix2Postfix("49*(41*39)-(145+78)+193+(121*135+101-88)") << endl;
    cout << Infix2Prefix("49*(41*39)-(145+78)+193+(121*135+101-88)") << endl;
    cout << PostfixPrefixCalculator("49*(41*39)-(145+78)+193+(121*135+101-88)") << endl;
    //t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->
    cout << LogicInfix2Postfix("t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->") << endl;
    cout << LogicInfix2Prefix("t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->") << endl;
    cout << LogicPostfixPrefixCalculator("t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->","t w z p q y x 1 1 1 1 1 1 1") << endl;
    return 0;
}