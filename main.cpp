///
/// \Authors Davis, Hunter
/// \file main.cpp
/// \note Main entry point for the class diagram tool. Uses all supporting classes and Dear ImGUI to create a class diagram of the files selected.
///


// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <unordered_map>
#include "GraphBuilder.hh"
#include "ImGuiFileDialog-0.6.4/ImGuiFileDialog.h"
#include "PrintOnPaper.h"

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

// Forward declarations of graph drawing fucntions
void initNodePositions(Graph<ClassInfo> graph);
void drawGraph(Graph<ClassInfo> graph, ImDrawList* drawList);
void drawNode(ClassInfo classInfo, ImVec2 pos, ImDrawList* drawList);
void displayClassInfo(ClassInfo classInfo, ImVec2 pos);

// Inline operators for ImVec2
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    //PrintOnPaper pop(4, 4);
    //pop.display();
    //PrintOnPaper::sudoMain();
    //return 0;

    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("C++ Class Diagram Tool"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool recursive = true;
    bool firstFrame = true;
    //Graph<ClassInfo> graph = GraphBuilder::build(R"(.\Examples)", recursive);
    Graph<ClassInfo> graph;

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();


        //
        // ClassDiagramTool code begin 
        //

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        // Initialize node positions
        if (firstFrame) {
            initNodePositions(graph);
            firstFrame = false;
        }

        // Directory input window
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 75));
        ImGui::Begin("directory input", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("C++ Source Directory:");
        static char buf[256] = "";
        ImGui::InputText(" ", buf, 256);
        ImGui::SameLine();
        if (ImGui::Button("Generate")) {
            //std::strcpy(buf, "test");
            try {
                graph = GraphBuilder::build(buf, recursive);
                initNodePositions(graph);
            }
            catch (std::filesystem::filesystem_error &e) {
                std::cout << e.what() << std::endl;
                std::cout << buf << std::endl;
            }
        }
        ImGui::Checkbox("Search Subfolders", &recursive);   
        ImGui::SameLine();
        if (ImGui::Button("Browse Folders")) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey", "Choose a Directory", nullptr, ".");
        }
        // display
        ImVec2 maxSize = ImVec2((float)viewport->Size.x, (float)viewport->Size.y);// The full display area
        ImVec2 minSize = ImVec2((float)viewport->Size.x/2, (float)viewport->Size.y/2);//maxSize * 0.5f;  // Half the display area
        if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey", ImGuiWindowFlags_NoCollapse, minSize, maxSize)){
        // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()){
                //std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName(); gives file name but we're slecting a dir so unnecessary
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                std::strcpy(buf, filePath.c_str());
                // action
            }

                // close
                ImGuiFileDialog::Instance()->Close();
            }
        
        ImGui::End();

        // Canvas
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 75));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - 75));
        ImGui::Begin("Class Diagram", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_HorizontalScrollbar);
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->ChannelsSplit(2);

        // Draw graph
        if (graph.getNodes().size() != 0)
            drawGraph(graph, drawList);
        drawList->ChannelsMerge();

        ImGui::End();
        
        // Demo window
        /*ImGui::SetNextItemOpen(false, ImGuiCond_Once);
        ImGui::ShowDemoWindow();*/

        //
        // ClassDiagramTool code end
        //


        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Draw graph fields/methods
const float nodeWidth = 110;
const float nodeHeight = 80;
const float pi = 3.142f;
const float quad1 = atan(nodeHeight/nodeWidth);
const float quad4 = -quad1;
const float quad2 = quad4 + pi;
const float quad3 = -quad2;
const float edgeWidth = 3.0f;
const int arrowSize = 20;
unsigned int baseColor = IM_COL32(127, 127, 127, 127);
unsigned int redColor = IM_COL32(127, 0, 0, 127);
std::unordered_map<int, ImVec2> nodeToPosMap; // Maps a node ID to the location of the window for that class info

// Initializes the positions for each node
void initNodePositions(Graph<ClassInfo> graph) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    nodeToPosMap.clear();
    graph.setPosition(viewport);
    for (Node<ClassInfo> node : graph.getNodes()) {
        ImVec2 nodePos = ImVec2(node.getX(), node.getY());
        nodeToPosMap.insert({ node.getID(), nodePos });
    }
    graph.getCross();
}

// Draws the class diagram
void drawGraph(Graph<ClassInfo> graph, ImDrawList* drawList) {
    //PrintOnPaper::nodeBs(graph);
    //std::getchar();
    ImVec2 scroll = ImVec2(-ImGui::GetScrollX(), -ImGui::GetScrollY());

    // Nodes
    for (Node<ClassInfo> node : graph.getNodes()) {
        auto search = nodeToPosMap.find(node.getID());
        if (search != nodeToPosMap.end()){
            ImVec2 nodePos = search->second;
            drawNode(node.getData(), nodePos + scroll, drawList);
        }
    }

    // Edges
    drawList->ChannelsSetCurrent(0);
    for (Edge<ClassInfo> edge : graph.getEdges()) {
        int startID = edge.getStartNode();
        int endID = edge.getEndNode();
        auto searchStart = nodeToPosMap.find(startID);
        auto searchEnd = nodeToPosMap.find(endID);

        if (searchStart != nodeToPosMap.end() && searchEnd != nodeToPosMap.end()) {
            ImVec2 startPos = searchStart->second + ImVec2(nodeWidth/2, nodeHeight/2);
            ImVec2 endPos = searchEnd->second + ImVec2(nodeWidth/2, nodeHeight/2);
            float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);

            // Determine which side of node to draw edge from
            if (angle < quad1 && angle >= quad4) {
                startPos = startPos + ImVec2(nodeWidth/2, 0);
                endPos = endPos + ImVec2(-nodeWidth/2, 0);
            } else if (angle < quad2 && angle >= quad1){
                startPos = startPos + ImVec2(0, nodeHeight/2);
                endPos = endPos + ImVec2(0, -nodeHeight/2);
            } else if ((angle < pi && angle >= quad2) || (angle >= -pi && angle < quad3)) {
                startPos = startPos + ImVec2(-nodeWidth/2, 0);
                endPos = endPos + ImVec2(nodeWidth/2, 0);
            } else if (angle < quad4 && angle >= quad3) {
                startPos = startPos + ImVec2(0, -nodeHeight/2);
                endPos = endPos + ImVec2(0, nodeHeight/2);
            }
            
            // Set color based on edge multiplicity
            unsigned int color = baseColor;
            

            // Draw line for edge
            drawList->AddLine(startPos + scroll, endPos + scroll, color, edgeWidth); 

            ImVec2 mPoint1;
            ImVec2 mPoint2;

            // Draw arrow heads based on edge type
            angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);
            ImVec2 point1 = endPos - ImVec2(arrowSize * cos(angle + pi/6), arrowSize * sin(angle + pi/6));
            ImVec2 point2 = endPos - ImVec2(arrowSize * cos(angle - pi/6), arrowSize * sin(angle - pi/6));
            switch (edge.getType()) {
            case Edge<ClassInfo>::Type::INHERITANCE:
                drawList->AddTriangleFilled(endPos + scroll, point1 + scroll, point2 + scroll, color);
                break;
            case Edge<ClassInfo>::Type::ASSOCIATION:
                drawList->AddLine(point1 + scroll, endPos + scroll, color, edgeWidth);
                drawList->AddLine(point2 + scroll, endPos + scroll, color, edgeWidth);

                // Display multiplicity characters 
                mPoint1 = endPos - ImVec2((arrowSize + 7.5) * cos(angle + pi / 8), (arrowSize + 7.5) * sin(angle + pi / 8)) + ImVec2(-3, -4);
                mPoint2 = startPos + ImVec2((arrowSize + 7.5) * cos(angle + pi / 8), (arrowSize + 7.5) * sin(angle + pi / 8)) + ImVec2(-3, -4);
                switch (edge.getMultiplicity()) {
                case Edge<ClassInfo>::Multiplicity::ONE_TO_ONE:
                    ImGui::SetCursorScreenPos(mPoint1 + scroll);
                    ImGui::Text("1");
                    /*ImGui::SetCursorScreenPos(mPoint2);
                    ImGui::Text("1");*/
                    break;
                case Edge<ClassInfo>::Multiplicity::ONE_TO_MANY:
                    ImGui::SetCursorScreenPos(mPoint1 + scroll);
                    ImGui::Text("n");
                    /*ImGui::SetCursorScreenPos(mPoint2);
                    ImGui::Text("1");*/
                    break;
                default:
                    break;
                }

                break;
            default:
                break;
            }
        } 
    }
}

// Draws a node
void drawNode(ClassInfo classInfo, ImVec2 pos, ImDrawList* drawList) {
    // Node contents
    drawList->ChannelsSetCurrent(1);
    ImGui::SetCursorScreenPos(pos + ImVec2(7.5f, 8.0f));
    ImGui::BeginGroup();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.10f, 0.10f, 0.10f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.20f, 0.20f, 0.20f, 0.5f));
    if (ImGui::Button(&classInfo.getName()[0], ImVec2(nodeWidth - 15, nodeHeight - 16)))
        ImGui::OpenPopup(&classInfo.getName()[0]);
    ImGui::PopStyleColor(2);
    displayClassInfo(classInfo, pos);
    ImGui::EndGroup();

    // Node box
    drawList->ChannelsSetCurrent(0);
    drawList->AddRectFilled(pos, pos + ImVec2(nodeWidth, nodeHeight), IM_COL32(10, 10, 10, 255));
    drawList->AddRect(pos, pos + ImVec2(nodeWidth, nodeHeight), IM_COL32(50, 50, 50, 255));
}

// Displays a popup showing the fields and methods of a class
void displayClassInfo(ClassInfo classInfo, ImVec2 pos) {
    if (ImGui::BeginPopup(&classInfo.getName()[0])) {
        
        // Fields
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Fields")) {
            for (Field field : classInfo.getFields()) {
                std::string fieldText;
                if (field.getScope() == "public") {
                    fieldText = "+ " + field.getName() + " : " + field.getType().toString();
                } else if (field.getScope() == "private") {
                    fieldText = "- " + field.getName() + " : " + field.getType().toString();
                } else {
                    fieldText = field.getName() + " : " + field.getType().toString();
                }
                ImGui::Text(&fieldText[0]);
            }
            ImGui::TreePop();
        }

        // Methods
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Methods")) {
            for (Method method : classInfo.getMethods()) {
                std::string methodText;
                if (method.getScope() == "public") {
                    methodText = "+ " + method.getName() + " : " + method.getType().toString();
                } else if (method.getScope() == "private") {
                    methodText = "- " + method.getName() + " : " + method.getType().toString();
                } else {
                    methodText = method.getName() + " : " + method.getType().toString();
                }
                ImGui::Text(&methodText[0]);
            }
            ImGui::TreePop();
        }
        ImGui::EndPopup();
    }
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
