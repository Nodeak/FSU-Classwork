#include <iostream>
#include "box.h" 
#include "messages.h" 
using namespace std;

int main(void)
{  
   Messages MyMessage; 
   Box mybox1(1,'*','<');  
   Box mybox2(2,'^','!');
   Box mybox3(3,')');         // box of size three with default fill
   Box mybox5(5);             // box of size five  with default border and fill 
   Box mybox10(10,'#','@'); 
   Box mybox39(39, '*','&'); 
   Box mybox41(49,' ',' ');    //Size should be set to 39 and default fill
			       //and border. . 
   MyMessage.PrintIntroduction(); 
   cout << "Draw a box of size 1, with * border and < fill" << endl; 
   mybox1.Draw();
   cout << "Try to shrink Box1, see if it stays at 1, Print Summery " << endl;
   mybox1.Shrink();
   mybox1.Summary();
   cout << " Try to change Border to a space, make sure it goes back to default of #" << endl;
   mybox1.SetBorder(' ');
   mybox1.Draw(); 
   cout << "Draw a box of size 2, with ^ border and ! fill" << endl;  
   mybox2.Draw();
   mybox2.Shrink();
   cout << "Shrink Box of Size 2, see if it goes to 1,Print Summary" << endl;
   mybox2.Summary(); 
   cout << "Box of Size 3 with default fill character, Print Summary" << endl; 
   mybox3.Summary(); 
   cout << "Box of Size 5 with default character and fill, Print Summary" << endl; 
   mybox5.Summary(); 
   cout << "Draw a box of size 10, with # border and @ fill" << endl;   
   mybox10.Draw();
   cout << "Grow Box of size 10, see if it goes to 11, Print Summary" << endl;
   mybox10.Grow();
   mybox10.Summary();
   cout<< "Try to set the fill character to a space, make sure it goes to the default of *" << endl;
   mybox10.SetFill(' ');
   mybox10.Draw(); 
   cout << "Draw a box of size 39, with * border and & fill" << endl;
   mybox39.Draw();
   cout << "Grow a box of size 39, see if it stays at 39, print summary"<< endl;
   mybox39.Grow();
   mybox39.Summary();
   cout << "Box 41 should be of size 39 with default characters" << endl;
   mybox41.Summary(); 
   cout <<"Test GetSize" << endl; 
   cout <<"Size is: "<< mybox41.GetSize() << endl; 
   
 
   return 0;
}

