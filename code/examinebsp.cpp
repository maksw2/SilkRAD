#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <bitset>

#include <cstdlib>

#include "bsp.h"

static BSP::BSP g_bsp;


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Invalid arguments." << std::endl;
        return 1;
    }
    
    const std::string filename(argv[1]);
    std::ifstream f(filename, std::ios::binary);
    
    try {
        g_bsp = BSP::BSP(filename);
    }
    catch (BSP::InvalidBSP e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "BSP Version " << g_bsp.get_format_version() << std::endl;
    std::cout << "Fullbright: " << g_bsp.is_fullbright() << std::endl;
    
    int i = 0;
    for (BSP::Face& face : g_bsp.get_faces()) {
        std::cout << "Face " << i << ":" << std::endl;
        
        for (const BSP::Edge& edge : face.get_edges()) {
            const BSP::Vec3& vertex1 = edge.vertex1;
            const BSP::Vec3& vertex2 = edge.vertex2;
            
            std::cout << "    ("
                << vertex1.x << ", "
                << vertex1.y << ", "
                << vertex1.z << ") -> ("
                << vertex2.x << ", "
                << vertex2.y << ", "
                << vertex2.z << ")"
                << std::endl;
        }
        
        std::cout <<  "    Styles:" << std::endl;
        
        int j = 0;
        for (uint8_t style : face.get_styles()) {
            std::cout << "        " << j << " "
                << std::bitset<sizeof(style) * 8>(style)
                << std::endl;
            j++;
        }
        
        const BSP::DFace& faceData = face.get_data();
        
        std::cout << "    Light Offset: "
            << faceData.lightOffset / sizeof(BSP::LightSample) << std::endl;
        
        std::cout << "    Luxels X: "
            << face.get_lightmap_width()
            << std::endl
            << "    Luxels Y: "
            << face.get_lightmap_height()
            << std::endl;
            
        std::vector<BSP::LightSample>& lightSamples = face.get_lightsamples();
        
        std::cout << "    "
            << lightSamples.size() << " Light Samples" << std::endl;
            
        const BSP::LightSample& avgLighting = face.get_average_lighting();
        
        std::cout << "    Average Lighting: ("
            << static_cast<int>(avgLighting.r) << ", "
            << static_cast<int>(avgLighting.g) << ", "
            << static_cast<int>(avgLighting.b) << ") * 2^"
            << static_cast<int>(avgLighting.exp) << std::endl;
            
        // std::cout << "    Light Samples:" << std::endl;
        
        // j = 0;
        // for (BSP::LightSample& lightSample : face.get_lightsamples()) {
            // std::cout << "        Sample " << j << ": ("
                // << static_cast<int>(lightSample.r) << ", "
                // << static_cast<int>(lightSample.g) << ", "
                // << static_cast<int>(lightSample.b) << ") * 2^"
                // << static_cast<int>(lightSample.exp) << std::endl;
            // j++;
        // }
        
        i++;
    }
    
    i = 0;
    for (const BSP::Light& light : g_bsp.get_lights()) {
        std::cout << "Light " << i << ":" << std::endl;
        
        const BSP::Vec3& pos = light.get_coords();
        std::cout << "    pos: ("
            << pos.x << ", "
            << pos.y << ", "
            << pos.z << ")" << std::endl;
            
        std::cout << "    r: " << light.r << std::endl;
        std::cout << "    g: " << light.g << std::endl;
        std::cout << "    b: " << light.b << std::endl;
        
        i++;
    }
    
    // std::cout << "Ent Data: " << std::endl;
    // std::cout << g_bsp.get_entdata() << std::endl;
    
    std::cout << "World Lights: " << std::endl;
    
    i = 0;
    for (const BSP::DWorldLight& worldLight : g_bsp.get_worldlights()) {
        std::cout << "    World Light " << i << ":" << std::endl;
        
        std::cout << "        origin: ("
            << worldLight.origin.x << ", "
            << worldLight.origin.y << ", "
            << worldLight.origin.z << ")" << std::endl;
            
        std::cout << "        intensity: ("
            << worldLight.intensity.x << ", "
            << worldLight.intensity.y << ", "
            << worldLight.intensity.z << ")" << std::endl;
            
        std::cout << "        normal: ("
            << worldLight.normal.x << ", "
            << worldLight.normal.y << ", "
            << worldLight.normal.z << ")" << std::endl;
            
        std::cout << "        cluster: " << worldLight.cluster << std::endl;
        std::cout << "        type: " << worldLight.type << std::endl;
        std::cout << "        style: " << worldLight.style << std::endl;
        std::cout << "        stopdot: " << worldLight.stopdot << std::endl;
        std::cout << "        stopdot2: " << worldLight.stopdot2 << std::endl;
        std::cout << "        exponent: " << worldLight.exponent << std::endl;
        std::cout << "        radius: " << worldLight.radius << std::endl;
        std::cout << "        const: " << worldLight.constantAtten << std::endl;
        std::cout << "        lin: " << worldLight.linearAtten << std::endl;
        std::cout << "        quad: " << worldLight.quadraticAtten << std::endl;
        std::cout << "        flags: " << worldLight.flags << std::endl;
        std::cout << "        texinfo: " << worldLight.texinfo << std::endl;
        std::cout << "        owner: " << worldLight.owner << std::endl;
        
        i++;
    }
    
    return 0;
}
