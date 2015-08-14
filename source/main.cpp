#include <windows.h>

#   define  IDC_CHECKBOX1                100   ///<Identifier For 1st Check Box 
#   define  IDC_CHECKBOX2                101   ///<Identifier For 2nd Check Box 
#   define  IDC_CHECKBOX3                102   ///<Identifier For 3rd Check Box 
#   define  IDC_CHECKBOX4                103   ///<Identifier For 4th Check Box
#   define  IDC_RADIO11          104         ///<Identifier For 1st Radio Button   
#   define  IDC_RADIO12          105         ///<Identifier For 2nd Radio Button 
#   define  IDC_RADIO13          106         ///<Identifier For 3rd Radio Button  
#   define  IDC_RADIO21          107         ///<Identifier For 1st Radio Button  
#   define  IDC_RADIO22          108         ///<Identifier For 2nd Radio Button  
#   define  IDC_RADIO23          109         ///<Identifier For 3rd Radio Button 
#   define  IDC_EDITBOX                  110         ///<Identifier For Edit Control 
#   define  IDC_LISTBOX          111         ///<Identifier For List Box 
#   define  IDC_SUBMIT                112            ///<Identifier For Submit Button 
#   define  IDC_GROUP1                  113            ///<Identifier For 1st Group 
#   define  IDC_GROUP2                  114            ///<Identifier For 2nd Group 
#   define  IDC_GROUP3                  115            ///<Identifier For 3rd Group 
#   define  IDC_RESET                    116   ///<Identifier For Reset Button 
#   define  IDC_COMBOBOX          117      ///<Identifier For Reset Button   
#   define      ONE                         1           ///<Macro Declaration.
#   define      TWO                         2           ///<Macro Declaration.
#   define      THREE                       3           ///<Macro Declaration.
#   define      FOUR                        4          ///<Macro Declaration.
#   define      ZERO                        0           ///<Macro Declaration.
#   define      FIVE                        5          ///<Macro Declaration.

void CreateControls(HWND phWnd);
void CreateLabels(HWND phWnd);
void CreateGroups(HWND phWnd);
void CreateRadioButtonfirstgroup(HWND phWnd, int y_axis);
void CreateRadioButtonsecondgroup(HWND hWnd, int y_axis);
void Createopbutton(HWND phWnd);
void CreateCheckBox(HWND phWnd, int y_axis);
void CreateComboBox(HWND phWnd);
void CreateEditBox(HWND phWnd);
void CreateListBox(HWND phWnd);
void AddItemsInListBox(HWND phWnd);
void radiocheck(int pButton_no, HWND phWnd);
void EditText(HWND phWnd);
void RetrieveTextFromComboBox(HWND phWnd);
wchar_t* RetrieveText(HWND hWnd);
void checkbox(HWND phwndCheckBox, HWND phWnd);

HINSTANCE    ghInstance;   ///< Contains the instance of the Application
int gCheckonce = ONE, i;      ///<used for the submit button to allow only one submission. 

const wchar_t g_szClassName[] = L"myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		CreateControls(hwnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:

		//Handling Window Controllers 
		switch (LOWORD(wParam)) {

		case IDC_SUBMIT:

			///<handles the submission of the details into the list box on clicking submit 

			if (HIWORD(wParam) == BN_CLICKED && gCheckonce == ONE) {  ///< hiword(wParam) takes the notification

				AddItemsInListBox(hwnd); ///<displays all the details in the list box.

				gCheckonce = TWO;
			}
			break;

		case IDC_RESET:

			if (HIWORD(wParam) == BN_CLICKED) {

				for (i = ZERO; i < FOUR; i++) {

					//sends message to uncheck the radio buttons of the first group.
					SendMessage(GetDlgItem(hwnd, (IDC_RADIO11 + i)), BM_SETCHECK, BST_UNCHECKED, 0);

					//sends message to uncheck the radio buttons of the second group
					SendMessage(GetDlgItem(hwnd, (IDC_RADIO21 + i)), BM_SETCHECK, BST_UNCHECKED, 0);

					//sends message to uncheck the check boxes.
					SendMessage(GetDlgItem(hwnd, (IDC_CHECKBOX1 + i)), BM_SETCHECK, BST_UNCHECKED, 0);
				}

				//sends message to reset the edit box.
				SendMessage(GetDlgItem(hwnd, IDC_EDITBOX), WM_SETTEXT, 0, (LPARAM)" ");

				//sends message to reset the combo box.
				SendMessage(GetDlgItem(hwnd, IDC_COMBOBOX), CB_SETCURSEL, 0, (LPARAM)"");

				//sends message to reset the list box.
				SendMessage(GetDlgItem(hwnd, IDC_LISTBOX), LB_RESETCONTENT, 0, 0);

				//resets the flag of the submit button to 1.
				gCheckonce = ONE;
			}
			break;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

auto WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) -> int
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"The title of my window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 950, 700,
		HWND_DESKTOP, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

void CreateControls(HWND phWnd)
{
	//TO CREATE COMBO BOX
	CreateComboBox(phWnd);

	//TO CREATE RADIOBUTTON
	CreateRadioButtonfirstgroup(phWnd, 180);

	//TO CREATE LABELS FOR ALL THE CONTROLS
	CreateLabels(phWnd);

	//TO CREATE THE GROUP STRUCTURE
	CreateGroups(phWnd);

	// CreateEditBox(phWnd);
	CreateEditBox(phWnd);

	//TO CREATE SECOND SET OF RADIOBUTTONS
	CreateRadioButtonsecondgroup(phWnd, 180);

	//TO CREATE CHECK BOX
	CreateCheckBox(phWnd, 340);

	//TO CREATE THE SUBMIT AND RESET BUTTONS FOR THE 1ST TAB
	Createopbutton(phWnd);

	//TO CREATE LIST BOX CONTROL 
	CreateListBox(phWnd);

	//used to setfocus on ComboBox
	SetFocus(GetDlgItem(phWnd, IDC_COMBOBOX));
}

void CreateLabels(HWND phWnd)
{

	//LABEL FOR THE COMBO BOX
	CreateWindowEx(0, L"Static", L"Enter the field of Study:", WS_CHILD | WS_VISIBLE | SS_LEFT, 40, 80, 200,
		20, phWnd, NULL, ghInstance, NULL);

	//LABEL FOR THE BADIOBUTTONS OF FIRST GROUP
	CreateWindowEx(0, L"Static", L"Enter the Students Year Of Study:", WS_CHILD | WS_VISIBLE | SS_LEFT, 40, 160, 250, 20, phWnd, NULL, ghInstance, NULL);

	//LABEL FOR THE EDIT BOX
	CreateWindowEx(0, L"Static", L"Enter the Students Name:", WS_CHILD | WS_VISIBLE | SS_LEFT, 510, 80, 180, 20, phWnd, NULL, ghInstance, NULL);

	//LABEL FOR THE RADIOBUTTONS OF THE SECOND GROUP
	CreateWindowEx(0, L"Static", L"Enter the Students Initials:", WS_CHILD | WS_VISIBLE | SS_LEFT, 510, 160, 180, 20,
		phWnd, NULL, ghInstance, NULL);

	//LABEL FOR THE CHECK BOX
	CreateWindowEx(0, L"Static", L"Enter the Students Hobbies:", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 350, 280, 20, phWnd, NULL, ghInstance, NULL);
}

/**
* CreateGroups() used to create groups for all the controls
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Parent Window
* @param [in]     hwndCheckBox  contains the address of the check box control
*
*/
void CreateGroups(HWND phWnd)
{
	//CREATES THE OUTLINE FOR THE FIRST GROUP
	CreateWindowEx(0, L"Button", L"SUBJECT DETAILS", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 30, 50, 400, 250, phWnd,
		(HMENU)IDC_GROUP1, ghInstance, NULL);

	//CREATES THE OUTLINE FOR THE SECOND GROUP
	CreateWindowEx(0, L"Button", L"STUDENT DETAILS", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 500, 50, 400,
		250, phWnd, (HMENU)IDC_GROUP2, ghInstance, NULL);

	//CREATES THE OUTLINE FOR THE THIRD GROUP
	CreateWindowEx(0, L"Button", L"HOBBIES", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 30, 320, 670,
		120, phWnd, (HMENU)IDC_GROUP3, ghInstance, NULL);

}


/**
* CreateRadioButtonfirstgroup() used to create Radio Button for first Group Box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Window
* @param [in]     button_no        Contains the Radio button no.
*
*/
void CreateRadioButtonfirstgroup(HWND phWnd, int y_axis)
{

	int i, x_axis;
	wchar_t *radiobuttonnames[] = { L"I",L"II",L"III" };

	//this loop creates the three radiobuttons.
	for (i = ZERO, x_axis = 50;i<THREE;i++, x_axis += 90) {

		CreateWindowEx(0, L"Button", radiobuttonnames[i], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,

			x_axis, y_axis, 50, 100, phWnd, (HMENU)(IDC_RADIO11 + i), ghInstance, NULL);
	}
}

/**
* CreateRadioButtonsecondgroup() used to create Radio Button for second Group Box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Window
* @param [in]     button_no        Contains the Radio button no.
*
*/

void CreateRadioButtonsecondgroup(HWND hWnd, int y_axis)
{

	int i, x_axis;
	wchar_t *radiobuttonnames1[] = { L"Mr",L"Miss",L"Mrs" };

	//this loop creates the three radiobuttons.
	for (i = ZERO, x_axis = 520;i<THREE;i++, x_axis += 90) {

		CreateWindowEx(0, L"Button", radiobuttonnames1[i], WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,

			x_axis, y_axis, 50, 100, hWnd, (HMENU)(IDC_RADIO21 + i), ghInstance, NULL);
	}
}

/**
* Createopbutton() used to create submit and reset button
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Window
* @param [in]     button_no        Contains the Radio button no.
*
*/

void Createopbutton(HWND phWnd)
{
	//CREATES THE SUBMIT BUTTON
	CreateWindowEx(0, L"Button", L"Submit", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 350, 600, 100, 30,
		phWnd, (HMENU)IDC_SUBMIT, ghInstance, NULL);

	//CREATES THE RESET BUTTON
	CreateWindowEx(0, L"Button", L"Reset", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 550, 600, 100, 30,
		phWnd, (HMENU)IDC_RESET, ghInstance, NULL);

}

/**
* CreateCheckBox() creates the check boxes
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Parent Window
* @param [in]     hwndCheckBox  contains the address of the check box control
*
*/

void CreateCheckBox(HWND phWnd, int y_axis)
{

	int x_axis, i;
	wchar_t *checkboxnames[] = { L"Singing",L"Dancing",L"Sketching",L"Drawing" };


	//this loop creates the four checkboxes.
	for (i = ZERO, x_axis = 50;i<FOUR;i++, x_axis += 150) {

		CreateWindowEx(0, L"Button", checkboxnames[i], WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP,
			x_axis, 390, 100, 15, phWnd, (HMENU)(IDC_CHECKBOX1 + i), ghInstance, NULL);

	}
}

/**
* CreateComboBox() used to create Combo Box For first Group Box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd  Contains the address of the Window
*
*/

void CreateComboBox(HWND phWnd)
{

	wchar_t    *comboitem[] = { L"SELECT",
		L"MATHS",
		L"BIOLOGY",
		L"COMMERCE",
		L"ARTS" };
	int  i;

	CreateWindowEx(0, L"COMBOBOX",
		L"",
		CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP,
		70,
		100,
		200,
		500,
		phWnd,
		(HMENU)IDC_COMBOBOX,
		ghInstance,
		NULL);

	//Add items in the Combo Box
	for (i = ZERO;i<FIVE;i++)
		SendMessage(GetDlgItem(phWnd, IDC_COMBOBOX), CB_ADDSTRING, 0, (LPARAM)comboitem[i]);

}

/**
* CreateEditBox() used to create submit and reset button
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Window
* @param [in]     button_no        Contains the Radio button no.
*
*/

void CreateEditBox(HWND phWnd)
{
	//CREATES THE EDIT BOX
	CreateWindowEx(0, L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP, 700, 70, 180, 40,
		phWnd, (HMENU)IDC_EDITBOX, ghInstance, NULL);
}

/**
* CreateListBox() used to create List Box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Window
*
*/

void CreateListBox(HWND phWnd)
{
	//CREATES THE LIST BOX
	CreateWindowEx(0, L"ListBox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, 200, 480, 200, 50, phWnd, (HMENU)IDC_LISTBOX, ghInstance, NULL);
}

/**
* AddItemsToListBox() used to retrieve text from all the controls and add those in List Box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd  Contains the address of the Window
*/

void AddItemsInListBox(HWND phWnd)
{
	//CALL FUNCTION TO RETRIEVE THE SELECTED STRING FROM THE COMBO BOX
	RetrieveTextFromComboBox(phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE CHECK BOX 1 SELECTD OR N0T
	checkbox(GetDlgItem(phWnd, IDC_CHECKBOX1), phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE CHECK BOX 2 IS SELECTD OR N0T
	checkbox(GetDlgItem(phWnd, IDC_CHECKBOX2), phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE CHECK BOX 3 IS SELECTD OR N0T
	checkbox(GetDlgItem(phWnd, IDC_CHECKBOX3), phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE CHECK BOX 3 IS SELECTD OR N0T
	checkbox(GetDlgItem(phWnd, IDC_CHECKBOX4), phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 1 OF RADIO GROUP 1 IS SELECTD OR N0T
	radiocheck(IDC_RADIO11, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 2 OF RADIO GROUP 1 IS SELECTD OR N0T
	radiocheck(IDC_RADIO12, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 3 OF RADIO GROUP 1 IS SELECTD OR N0T
	radiocheck(IDC_RADIO13, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 1 OF RADIO GROUP 2 IS SELECTD OR N0T
	radiocheck(IDC_RADIO21, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 2 OF RADIO GROUP 2 IS SELECTD OR N0T
	radiocheck(IDC_RADIO22, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE RADIO BUTTON 3 OF RADIO GROUP 2 IS SELECTD OR N0T
	radiocheck(IDC_RADIO23, phWnd);

	//CALL FUNCTION TO CHECK THAT WEATHER THE TEXT IS AVILABLE IN EDIT CONTROL OR N0T
	EditText(phWnd);
}
/**
* radiocheck() used to check whether or not Radio Buttons are checked
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd   Contains the address of the Window
* @param [in]     Button_no    Identifier of Radio Button.
*
*/

void radiocheck(int pButton_no, HWND phWnd)
{

	wchar_t*      edittext;
	int   i;

	//RETURN TRUE IF RADIO BUTTON IS SELECTED
	if (SendMessage(GetDlgItem(phWnd, pButton_no), BM_GETCHECK, 0, 0) == BST_CHECKED) {

		//Retrieve the length of the text associated with the CheckBox 
		i = GetWindowTextLength(GetDlgItem(phWnd, pButton_no));

		//Allocate memory of i length
		edittext = new wchar_t[10 * (i + 1)*sizeof(wchar_t)];

		//Retrieve the string associated with the Radio Buttons 
		GetWindowText(GetDlgItem(phWnd, pButton_no), edittext, i + 1);

		//Add that string in to the List box
		SendMessage(GetDlgItem(phWnd, IDC_LISTBOX), LB_ADDSTRING, 0, (LPARAM)edittext);
		delete[] edittext;
	}
}

/**
* EditText() used to retrieve text from Edit Text control of first group box and add it to the list box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd  Contains the address of the Window
*
*/


void EditText(HWND phWnd)
{

	wchar_t    *edittext;        ///<contains the address of the Buffer                                        

								 //call RetrieveText() to retrieve text from the Edit Control of First Group Box
	edittext = RetrieveText(GetDlgItem(phWnd, IDC_EDITBOX));

	//add that string in the List box
	SendMessage(GetDlgItem(phWnd, IDC_LISTBOX), LB_ADDSTRING, 0, (LPARAM)edittext);
	delete[] edittext;
}
/**
* RetrieveTextFromComboBox() used to retrieve selected text from combo box
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd  Contains the address of the Window
*
*/
void RetrieveTextFromComboBox(HWND phWnd)
{

	wchar_t    *edittext;
	int  CBIndex;

	CBIndex = SendMessage(GetDlgItem(phWnd, IDC_COMBOBOX), CB_GETCURSEL, 0, 0);

	//checks whether or not any value is selected in the combo box if not retuns -1
	if (CBIndex != -1) {

		edittext = RetrieveText(GetDlgItem(phWnd, IDC_COMBOBOX));
		//ADD THE RETRIEVED TEXT TO THE LIST BOX 
		SendMessage(GetDlgItem(phWnd, IDC_LISTBOX), LB_ADDSTRING, 0, (LPARAM)edittext);

		delete[] edittext;
	}
}

/**
* RetrieveText() used to retireve text from th edit control
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd  Contains the address of the Window
*
*/
wchar_t* RetrieveText(HWND hWnd)
{
	wchar_t        *edittext;
	int   textlength;


	//Retrieve text length 
	textlength = SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
	edittext = new wchar_t[(textlength + 1) * sizeof(wchar_t)];

	//retrieve the string entered in the Edit Control 
	SendMessage(hWnd, WM_GETTEXT, textlength + 1, (LPARAM)edittext);

	return edittext;
}
/**
* checkbox() used to check whether or not check boxes are checked
*
* This continues into the more detailed description of the function.
*
* @param [in]     hWnd    Contains the address of the Parent Window
* @param [in]     hwndCheckBox  contains the address of the check box control
*
*/

void checkbox(HWND phwndCheckBox, HWND phWnd)
{

	wchar_t *    edittext;
	int   i;

	//RETURN TRUE IF CHECK BOX IS SELECTED
	if (SendMessage(phwndCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED) {

		//retrieve the length of the text associated with the CheckBox 
		i = GetWindowTextLength(phwndCheckBox);

		//Allocate memory of i length
		edittext = new wchar_t[(10 * (i + 1))*sizeof(char)];

		//retrieve the string associated with the CheckBox 
		i = GetWindowText(phwndCheckBox, edittext, (i + 1));

		//add that string in to the List box
		SendMessage(GetDlgItem(phWnd, IDC_LISTBOX), LB_ADDSTRING, 0, (LPARAM)edittext);

		delete[] edittext;
	}
}