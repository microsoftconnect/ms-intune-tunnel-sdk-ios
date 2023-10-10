// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "MicrosoftIntuneTunnelSDK",
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "MicrosoftIntuneTunnelSDK",
            targets: ["MicrosoftIntuneTunnelSDK"]),
    ],
    targets: [
        .target(name: "MicrosoftIntuneTunnelSDK",
                dependencies: [
                    "ssl",
                    "crypto",
                    "MCPCommon",
                    "MCPCore",
                    "MCPPluginUnencryptedFile",
                    "MSTAPNextPluginSecurityOpenssl",
                    "MSTAPNextPluginVpnMicrosoftTunnel",
                    "MicrosoftTunnelApi"
                ]),
        .binaryTarget(name: "ssl", path: "ssl.xcframework"),
        .binaryTarget(name: "crypto", path: "crypto.xcframework"),
        .binaryTarget(name: "MCPCommon", path: "MCPCommon.xcframework"),
        .binaryTarget(name: "MCPCore", path: "MCPCore.xcframework"),
        .binaryTarget(name: "MCPPluginUnencryptedFile", path: "MCPPluginUnencryptedFile.xcframework"),
        .binaryTarget(name: "MSTAPNextPluginSecurityOpenssl", path: "MSTAPNextPluginSecurityOpenssl.xcframework"),
        .binaryTarget(name: "MSTAPNextPluginVpnMicrosoftTunnel", path: "MSTAPNextPluginVpnMicrosoftTunnel.xcframework"),
        .binaryTarget(name: "MicrosoftTunnelApi", path: "MicrosoftTunnelApi.xcframework"),
    ]
)
