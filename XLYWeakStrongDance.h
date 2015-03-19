//
//  XLYWeakStrongDance.h
//
//  Created by kaizei on 14/11/29.
//  Copyright (c) 2014年 kaizei. All rights reserved.
//

#ifndef XLYWeakStrongDance_h
#define XLYWeakStrongDance_h

/*
 *  self is not keyword in objective-c. it can be used as variable.
 *  so, you can use XLYMakeStrong(self) to create a local variable named 'self' in block which hides the origin self.
 */

/*
    XLYMakeWeak(self); //create a local weak variable named 'self_weak_'
    dispatch_async(nil, ^{
    
        // will create a local strong variable named 'self' and no capture will happen.
        XLYMakeStrong(self);
    
        //will create a local strong variable named 'strongSelf'.
        XLYMakeStrongWithVariable(self, strongSelf);
    });
*/

///creat a weak variable. if the input param is 'arg', the weak variable is 'arg_weak_'
#define XLYMakeWeak(arg) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wshadow\"") \
__weak __typeof(arg) arg##_weak_ = arg; \
_Pragma("clang diagnostic pop")

///create a strong variable based on the XLYMakeWeak macro. the new variable uses the same name as arg.
#define XLYMakeStrong(arg) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wshadow\"") \
__strong __typeof(arg##_weak_) arg = arg##_weak_ \
_Pragma("clang diagnostic pop")

///create a strong variable based on the XLYMakeWeak macro. the new variable uses the var as name.
#define XLYMakeStrongWithVariable(arg, var) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wshadow\"") \
__strong __typeof(arg##_weak_) var = arg##_weak_ \
_Pragma("clang diagnostic pop")

///helper macro. add a return statement if the strong arg is nil.
#define XLYMakeStrongAndReturnIfNil(arg) \
XLYMakeStrong(arg); \
if (!arg) return

///helper macro. add a return statement if var is nil.
#define XLYMakeStrongWithVariableAndReturnIfNil(arg, var) \
XLYMakeStrongWithVariable(arg, var); \
if (!var) return

#endif
