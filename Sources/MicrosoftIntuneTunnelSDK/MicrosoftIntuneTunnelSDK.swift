import Foundation
import MicrosoftTunnelApi

open class MicrosoftTunnelDelegate : NSObject, MicrosoftTunnelApi.MicrosoftTunnelDelegate {
   
    public static var instance: MicrosoftTunnelDelegate = MicrosoftTunnelDelegate()
    
    private let config: NSMutableDictionary = NSMutableDictionary.init()
    private let api: MicrosoftTunnel = MicrosoftTunnel.sharedInstance
    
    private override init(){
        super.init()
    }
    
    open func launch(){
        if !api.launchEnrollment()  {
            let error = api.microsoftTunnelInitialize(with: self, logDelegate: LogDelegate(), config: (self.config as! [String : String]))
            if error != NoError {
                NSLog("Failed to initialize MicrosoftTunnel API!")
            }
        }
    }
    
    open func signout(){
        if !api.launchUnenrollment(true)  {
            let error = api.microsoftTunnelInitialize(with: self, logDelegate: LogDelegate(), config: (self.config as! [String : String]))
            if error != NoError {
                NSLog("Failed to initialize MicrosoftTunnel API!")
            }
        }
    }
    
    public func handleMSALResponse(_ response: URL, _ sourceApplication: String) -> Bool {
        return api.handleMSALResponse(response, sourceApplication: sourceApplication)
    }
    
    // MARK: MicrosoftTunnelDelegate Protocol Stubs
    
    open func onReceivedEvent(_ event: MicrosoftTunnelStatus) {
        
    }
    
    open func onInitialized() {
        
    }
    
    open func onConnected() {
        
    }
    
    open func onReconnecting() {
        
    }
    
    open func onUserInteractionRequired() {
        
    }
    
    open func onDisconnected() {
        
    }
    
    open func onError(_ error: MicrosoftTunnelError) {
        
    }
}

public class LogDelegate: NSObject, MicrosoftTunnelApi.MicrosoftTunnelLogDelegate {
    public func logMessage(_ level: UInt32, logClass: UInt32, pTime: UnsafePointer<CChar>, pLevel: UnsafePointer<CChar>, pClassLabel: UnsafePointer<CChar>, pLog: UnsafePointer<CChar>) {
        NSLog("%s [%s] [%d] %s", pLevel, pClassLabel, pthread_mach_thread_np(pthread_self()), pLog)
    }
}
