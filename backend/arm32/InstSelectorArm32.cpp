///
/// @file InstSelectorArm32.cpp
/// @brief 指令选择器-ARM32的实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#include <cstdio>

#include "Common.h"
#include "ILocArm32.h"
#include "InstSelectorArm32.h"
#include "PlatformArm32.h"

#include "PointerType.h"
#include "RegVariable.h"
#include "Function.h"

#include "LabelInstruction.h"
#include "GotoInstruction.h"
#include "FuncCallInstruction.h"
#include "MoveInstruction.h"

/// @brief 构造函数
/// @param _irCode 指令
/// @param _iloc ILoc
/// @param _func 函数
InstSelectorArm32::InstSelectorArm32(vector<Instruction *> & _irCode,
                                     ILocArm32 & _iloc,
                                     Function * _func,
                                     SimpleRegisterAllocator & allocator)
    : ir(_irCode), iloc(_iloc), func(_func), simpleRegisterAllocator(allocator)
{
    translator_handlers[IRInstOperator::IRINST_OP_ENTRY] = &InstSelectorArm32::translate_entry;
    translator_handlers[IRInstOperator::IRINST_OP_EXIT] = &InstSelectorArm32::translate_exit;

    translator_handlers[IRInstOperator::IRINST_OP_LABEL] = &InstSelectorArm32::translate_label;
    translator_handlers[IRInstOperator::IRINST_OP_GOTO] = &InstSelectorArm32::translate_goto;

    translator_handlers[IRInstOperator::IRINST_OP_ASSIGN] = &InstSelectorArm32::translate_assign;
    translator_handlers[IRInstOperator::IRINST_OP_MOVE] = &InstSelectorArm32::translate_move;

    translator_handlers[IRInstOperator::IRINST_OP_ADD_I] = &InstSelectorArm32::translate_add_int32;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_I] = &InstSelectorArm32::translate_sub_int32;

    // 注册乘法、除法和取余的翻译函数
    translator_handlers[IRInstOperator::IRINST_OP_MUL_I] = &InstSelectorArm32::translate_mul_int32;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_I] = &InstSelectorArm32::translate_div_int32;
    translator_handlers[IRInstOperator::IRINST_OP_MOD_I] = &InstSelectorArm32::translate_mod_int32;

    translator_handlers[IRInstOperator::IRINST_OP_FUNC_CALL] = &InstSelectorArm32::translate_call;
    translator_handlers[IRInstOperator::IRINST_OP_ARG] = &InstSelectorArm32::translate_arg;

    // 注册关系运算符翻译函数
    translator_handlers[IRInstOperator::IRINST_OP_LT] = &InstSelectorArm32::translate_cmp_lt;
    translator_handlers[IRInstOperator::IRINST_OP_GT] = &InstSelectorArm32::translate_cmp_gt;
    translator_handlers[IRInstOperator::IRINST_OP_LE] = &InstSelectorArm32::translate_cmp_le;
    translator_handlers[IRInstOperator::IRINST_OP_GE] = &InstSelectorArm32::translate_cmp_ge;
    translator_handlers[IRInstOperator::IRINST_OP_EQ] = &InstSelectorArm32::translate_cmp_eq;
    translator_handlers[IRInstOperator::IRINST_OP_NEQ] = &InstSelectorArm32::translate_cmp_neq;
    
    // 注册逻辑运算符翻译函数
    translator_handlers[IRInstOperator::IRINST_OP_AND] = &InstSelectorArm32::translate_logic_and;
    translator_handlers[IRInstOperator::IRINST_OP_OR] = &InstSelectorArm32::translate_logic_or;
    translator_handlers[IRInstOperator::IRINST_OP_NOT] = &InstSelectorArm32::translate_logic_not;
    
    // 注册条件分支指令翻译函数
    translator_handlers[IRInstOperator::IRINST_OP_COND_GOTO] = &InstSelectorArm32::translate_cond_goto;
    
    // 注册求负指令翻译函数
    translator_handlers[IRInstOperator::IRINST_OP_NEG_I] = &InstSelectorArm32::translate_neg_int32;
}

///
/// @brief 析构函数
///
InstSelectorArm32::~InstSelectorArm32()
{}

/// @brief 指令选择执行
void InstSelectorArm32::run()
{
    for (auto inst: ir) {

        // 逐个指令进行翻译
        if (!inst->isDead()) {
            translate(inst);
        }
    }
}

/// @brief 指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate(Instruction * inst)
{
    // 操作符
    IRInstOperator op = inst->getOp();

    map<IRInstOperator, translate_handler>::const_iterator pIter;
    pIter = translator_handlers.find(op);
    if (pIter == translator_handlers.end()) {
        // 没有找到，则说明当前不支持
        printf("Translate: Operator(%d) not support", (int) op);
        return;
    }

    // 开启时输出IR指令作为注释
    if (showLinearIR) {
        outputIRInstruction(inst);
    }

    (this->*(pIter->second))(inst);
}

///
/// @brief 输出IR指令
///
void InstSelectorArm32::outputIRInstruction(Instruction * inst)
{
    std::string irStr;
    inst->toString(irStr);
    if (!irStr.empty()) {
        iloc.comment(irStr);
    }
}

/// @brief NOP翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_nop(Instruction * inst)
{
    (void) inst;
    iloc.nop();
}

/// @brief Label指令指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_label(Instruction * inst)
{
    Instanceof(labelInst, LabelInstruction *, inst);

    iloc.label(labelInst->getName());
}

/// @brief goto指令指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_goto(Instruction * inst)
{
    Instanceof(gotoInst, GotoInstruction *, inst);

    // 无条件跳转
    iloc.jump(gotoInst->getTarget()->getName());
}

/// @brief 函数入口指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_entry(Instruction * inst)
{
    // 查看保护的寄存器
    auto & protectedRegNo = func->getProtectedReg();
    auto & protectedRegStr = func->getProtectedRegStr();

    bool first = true;
    for (auto regno: protectedRegNo) {
        if (first) {
            protectedRegStr = PlatformArm32::regName[regno];
            first = false;
        } else {
            protectedRegStr += "," + PlatformArm32::regName[regno];
        }
    }

    if (!protectedRegStr.empty()) {
        iloc.inst("push", "{" + protectedRegStr + "}");
    }

    // 为fun分配栈帧，含局部变量、函数调用值传递的空间等
    iloc.allocStack(func, ARM32_TMP_REG_NO);
}

/// @brief 函数出口指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_exit(Instruction * inst)
{
    if (inst->getOperandsNum()) {
        // 存在返回值
        Value * retVal = inst->getOperand(0);

        // 赋值给寄存器R0
        iloc.load_var(0, retVal);
    }

    // 恢复栈空间
    iloc.inst("mov", "sp", "fp");

    // 保护寄存器的恢复
    auto & protectedRegStr = func->getProtectedRegStr();
    if (!protectedRegStr.empty()) {
        iloc.inst("pop", "{" + protectedRegStr + "}");
    }

    iloc.inst("bx", "lr");
}

/// @brief 赋值指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_assign(Instruction * inst)
{
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);

    int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();

    if (arg1_regId != -1) {
        // 寄存器 => 内存
        // 寄存器 => 寄存器

        // r8 -> rs 可能用到r9
        iloc.store_var(arg1_regId, result, ARM32_TMP_REG_NO);
    } else if (result_regId != -1) {
        // 内存变量 => 寄存器

        iloc.load_var(result_regId, arg1);
    } else {
        // 内存变量 => 内存变量

        int32_t temp_regno = simpleRegisterAllocator.Allocate();

        // arg1 -> r8
        iloc.load_var(temp_regno, arg1);

        // r8 -> rs 可能用到r9
        iloc.store_var(temp_regno, result, ARM32_TMP_REG_NO);

        simpleRegisterAllocator.free(temp_regno);
    }
}

void InstSelectorArm32::translate_move(Instruction * inst)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);

    int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();

    if (arg1_regId != -1) {
        // 寄存器 => 内存
        // 寄存器 => 寄存器

        // r8 -> rs 可能用到r9
        iloc.store_var(arg1_regId, result, ARM32_TMP_REG_NO);
    } else if (result_regId != -1) {
        // 内存变量 => 寄存器

        iloc.load_var(result_regId, arg1);
    } else {
        // 内存变量 => 内存变量

        int32_t temp_regno = simpleRegisterAllocator.Allocate();

        // arg1 -> r8
        iloc.load_var(temp_regno, arg1);

        // r8 -> rs 可能用到r9
        iloc.store_var(temp_regno, result, ARM32_TMP_REG_NO);

        simpleRegisterAllocator.free(temp_regno);
    }
}

/// @brief 二元操作指令翻译成ARM32汇编
/// @param inst IR指令
/// @param operator_name 操作码
/// @param rs_reg_no 结果寄存器号
/// @param op1_reg_no 源操作数1寄存器号
/// @param op2_reg_no 源操作数2寄存器号
void InstSelectorArm32::translate_two_operator(Instruction * inst, string operator_name)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.Allocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.Allocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.Allocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }

    // r8 + r9 -> r10
    iloc.inst(operator_name,
              PlatformArm32::regName[load_result_reg_no],
              PlatformArm32::regName[load_arg1_reg_no],
              PlatformArm32::regName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM32_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.free(arg1);
    simpleRegisterAllocator.free(arg2);
    simpleRegisterAllocator.free(result);
}

/// @brief 整数加法指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_add_int32(Instruction * inst)
{
    translate_two_operator(inst, "add");
}

/// @brief 整数减法指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_sub_int32(Instruction * inst)
{
    translate_two_operator(inst, "sub");
}
//乘法
void InstSelectorArm32::translate_mul_int32(Instruction * inst)
{
    translate_two_operator(inst, "mul");
}

//除法
void InstSelectorArm32::translate_div_int32(Instruction * inst)
{
    translate_two_operator(inst, "sdiv");
}

//取余
void InstSelectorArm32::translate_mod_int32(Instruction * inst)
{
    Value * dividend = inst->getOperand(0);
    Value * divisor = inst->getOperand(1);
    Value * result = inst;

    // 分配寄存器
    int32_t dividend_reg = simpleRegisterAllocator.Allocate(dividend);
    int32_t divisor_reg = simpleRegisterAllocator.Allocate(divisor);
    int32_t quotient_reg = simpleRegisterAllocator.Allocate();
    int32_t temp_reg = simpleRegisterAllocator.Allocate();
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载被除数到寄存器
    iloc.load_var(dividend_reg, dividend);

    // 加载除数到寄存器
    iloc.load_var(divisor_reg, divisor);
    // 计算商：quotient = dividend / divisor
    iloc.inst("sdiv",
              PlatformArm32::regName[quotient_reg],
              PlatformArm32::regName[dividend_reg],
              PlatformArm32::regName[divisor_reg]);

    // 计算乘积：temp = quotient * divisor
    iloc.inst("mul",
              PlatformArm32::regName[temp_reg],
              PlatformArm32::regName[quotient_reg],
              PlatformArm32::regName[divisor_reg]);

    // 计算余数：result = dividend - temp
    iloc.inst("sub",
              PlatformArm32::regName[result_reg],
              PlatformArm32::regName[dividend_reg],
              PlatformArm32::regName[temp_reg]);

    // 将结果存储到目标变量
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(dividend);
    simpleRegisterAllocator.free(divisor);
    simpleRegisterAllocator.free(quotient_reg);
    simpleRegisterAllocator.free(temp_reg);
    simpleRegisterAllocator.free(result);
}

/// @brief 函数调用指令翻译成ARM32汇编
/// @param inst IR指令
void InstSelectorArm32::translate_call(Instruction * inst)
{
    FuncCallInstruction * callInst = dynamic_cast<FuncCallInstruction *>(inst);
    if (!callInst) {
        minic_log(LOG_ERROR, "translate_call: 类型转换失败");
        return;
    }

    int32_t operandNum = callInst->getOperandsNum();

    // 重置参数计数
    realArgCount = 0;
    
    // 处理参数
    if (operandNum > 0) {
        // 前四个参数通过寄存器传递
        for (int32_t k = 0; k < operandNum && k < 4; k++) {
            Value* arg = callInst->getOperand(k);
            if (!arg) continue;
            
            // 加载参数到对应寄存器
            iloc.load_var(k, arg);
        }
        
        // 超过4个的参数通过栈传递
        int esp = 0;
        for (int32_t k = 4; k < operandNum; k++) {
            Value* arg = callInst->getOperand(k);
            if (!arg) continue;
            
            // 加载参数到临时寄存器
            int32_t tempReg = 8; // 使用r8作为临时寄存器
            iloc.load_var(tempReg, arg);
            
            // 将临时寄存器的值存入栈
            iloc.store_base(tempReg, ARM32_SP_REG_NO, esp, ARM32_TMP_REG_NO);
            esp += 4; // 假设每个参数是4字节
        }
    }

    // 生成函数调用指令
    iloc.call_fun(callInst->getName());
    
    // 处理函数返回值
    if (!callInst->getType()->isVoidType()) {
        // 将r0寄存器的返回值存储到结果变量
        iloc.store_var(0, callInst, ARM32_TMP_REG_NO);
    }
}

///
/// @brief 实参指令翻译成ARM32汇编
/// @param inst
///
void InstSelectorArm32::translate_arg(Instruction * inst)
{
    // 翻译之前必须确保源操作数要么是寄存器，要么是内存，否则出错。
    Value * src = inst->getOperand(0);

    // 当前统计的ARG指令个数
    int32_t regId = src->getRegId();

    if (realArgCount < 4) {
        // 前四个参数
        if (regId != -1) {
            if (regId != realArgCount) {
                // 肯定寄存器分配有误
                minic_log(LOG_ERROR, "第%d个ARG指令对象寄存器分配有误: %d", realArgCount + 1, regId);
            }
        } else {
            minic_log(LOG_ERROR, "第%d个ARG指令对象不是寄存器", realArgCount + 1);
        }
    } else {
        // 必须是内存分配，若不是则出错
        int32_t baseRegId;
        bool result = src->getMemoryAddr(&baseRegId);
        if ((!result) || (baseRegId != ARM32_SP_REG_NO)) {

            minic_log(LOG_ERROR, "第%d个ARG指令对象不是SP寄存器寻址", realArgCount + 1);
        }
    }

    realArgCount++;
}

/// @brief 通用比较指令处理函数
void InstSelectorArm32::translate_cmp_common(Instruction * inst, const std::string &condition)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    // 分配寄存器
    int32_t arg1_reg = simpleRegisterAllocator.Allocate(arg1);
    int32_t arg2_reg = simpleRegisterAllocator.Allocate(arg2);
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载操作数
    iloc.load_var(arg1_reg, arg1);
    iloc.load_var(arg2_reg, arg2);

    // 比较两个值
    iloc.inst("cmp", 
              PlatformArm32::regName[arg1_reg], 
              PlatformArm32::regName[arg2_reg]);
    
    // 根据条件设置结果 (0 或 1)
    iloc.inst("mov", 
              PlatformArm32::regName[result_reg], 
              "#0");
    
    iloc.inst(condition, 
              PlatformArm32::regName[result_reg], 
              "#1");
    
    // 存储结果
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(arg1);
    simpleRegisterAllocator.free(arg2);
    simpleRegisterAllocator.free(result);
}

/// @brief 小于比较
void InstSelectorArm32::translate_cmp_lt(Instruction * inst)
{
    translate_cmp_common(inst, "movlt");
}

/// @brief 大于比较
void InstSelectorArm32::translate_cmp_gt(Instruction * inst)
{
    translate_cmp_common(inst, "movgt");
}

/// @brief 小于等于比较
void InstSelectorArm32::translate_cmp_le(Instruction * inst)
{
    translate_cmp_common(inst, "movle");
}

/// @brief 大于等于比较
void InstSelectorArm32::translate_cmp_ge(Instruction * inst)
{
    translate_cmp_common(inst, "movge");
}

/// @brief 等于比较
void InstSelectorArm32::translate_cmp_eq(Instruction * inst)
{
    translate_cmp_common(inst, "moveq");
}

/// @brief 不等于比较
void InstSelectorArm32::translate_cmp_neq(Instruction * inst)
{
    translate_cmp_common(inst, "movne");
}

/// @brief 逻辑与操作
void InstSelectorArm32::translate_logic_and(Instruction * inst)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    if (!arg1 || !arg2) {
        minic_log(LOG_ERROR, "逻辑与操作的操作数不完整");
        return;
    }

    // 分配寄存器
    int32_t arg1_reg = simpleRegisterAllocator.Allocate(arg1);
    int32_t arg2_reg = simpleRegisterAllocator.Allocate(arg2);
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载操作数
    iloc.load_var(arg1_reg, arg1);
    iloc.load_var(arg2_reg, arg2);

    // 更简单的实现：直接使用AND指令，然后规范化结果
    iloc.inst("and", 
              PlatformArm32::regName[result_reg], 
              PlatformArm32::regName[arg1_reg], 
              PlatformArm32::regName[arg2_reg]);

    // 规范化结果为布尔值(0或1)
    iloc.inst("cmp", PlatformArm32::regName[result_reg], "#0");
    iloc.inst("movne", PlatformArm32::regName[result_reg], "#1");

    // 存储结果
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(arg1);
    simpleRegisterAllocator.free(arg2);
    simpleRegisterAllocator.free(result);
}

/// @brief 逻辑或操作
void InstSelectorArm32::translate_logic_or(Instruction * inst)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    if (!arg1 || !arg2) {
        minic_log(LOG_ERROR, "逻辑或操作的操作数不完整");
        return;
    }

    // 分配寄存器
    int32_t arg1_reg = simpleRegisterAllocator.Allocate(arg1);
    int32_t arg2_reg = simpleRegisterAllocator.Allocate(arg2);
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载操作数
    iloc.load_var(arg1_reg, arg1);
    iloc.load_var(arg2_reg, arg2);

    // 更简单的实现：直接使用ORR指令，然后规范化结果
    iloc.inst("orr", 
              PlatformArm32::regName[result_reg], 
              PlatformArm32::regName[arg1_reg], 
              PlatformArm32::regName[arg2_reg]);

    // 规范化结果为布尔值(0或1)
    iloc.inst("cmp", PlatformArm32::regName[result_reg], "#0");
    iloc.inst("movne", PlatformArm32::regName[result_reg], "#1");

    // 存储结果
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(arg1);
    simpleRegisterAllocator.free(arg2);
    simpleRegisterAllocator.free(result);
}

/// @brief 逻辑非操作
void InstSelectorArm32::translate_logic_not(Instruction * inst)
{
    Value * result = inst;
    Value * arg = getSafeOperand(inst, 0);
    
    if (!arg) {
        minic_log(LOG_ERROR, "逻辑非操作的操作数为空或不存在");
        return;
    }

    // 分配寄存器
    int32_t arg_reg = simpleRegisterAllocator.Allocate(arg);
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载操作数
    iloc.load_var(arg_reg, arg);

    // 执行逻辑非操作 - 比较是否等于0
    iloc.inst("cmp", PlatformArm32::regName[arg_reg], "#0");
    iloc.inst("moveq", PlatformArm32::regName[result_reg], "#1");  // 如果等于0，结果是1
    iloc.inst("movne", PlatformArm32::regName[result_reg], "#0");  // 如果不等于0，结果是0

    // 存储结果
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(arg_reg);
    simpleRegisterAllocator.free(result_reg);
}

/// @brief 条件分支指令翻译
void InstSelectorArm32::translate_cond_goto(Instruction * inst)
{
    // 确保有足够的操作数
    if (inst->getOperandsNum() < 3) {
        minic_log(LOG_ERROR, "条件分支指令参数不足");
        return;
    }

    // 安全地获取操作数
    Value * cond = getSafeOperand(inst, 0);
    Value * trueLabel = getSafeOperand(inst, 1);
    Value * falseLabel = getSafeOperand(inst, 2);
    
    if (!cond || !trueLabel || !falseLabel) {
        minic_log(LOG_ERROR, "条件分支指令的操作数为空");
        return;
    }

    // 获取标签名称
    std::string trueLabelName, falseLabelName;
    LabelInstruction* trueLabelInst = dynamic_cast<LabelInstruction*>(trueLabel);
    LabelInstruction* falseLabelInst = dynamic_cast<LabelInstruction*>(falseLabel);
    
    if (!trueLabelInst) {
        minic_log(LOG_ERROR, "条件分支真标签非法");
        return;
    }
    trueLabelName = trueLabelInst->getName();
    
    if (!falseLabelInst) {
        minic_log(LOG_ERROR, "条件分支假标签非法");
        return;
    }
    falseLabelName = falseLabelInst->getName();

    // 加载条件值到寄存器
    int32_t cond_reg = simpleRegisterAllocator.Allocate(cond);
    iloc.load_var(cond_reg, cond);

    // 判断条件值是否为真（非0）
    iloc.inst("cmp", PlatformArm32::regName[cond_reg], "#0");
    
    // 使用更简单的跳转模式，避免多次调度
    iloc.inst("beq", falseLabelName); // 如果等于0(假)，跳转到false标签
    iloc.inst("b", trueLabelName);    // 否则(非0，为真)跳转到true标签

    // 释放寄存器
    simpleRegisterAllocator.free(cond_reg);
}

/// @brief 负数指令翻译
void InstSelectorArm32::translate_neg_int32(Instruction * inst)
{
    // 安全检查
    if (inst->getOperandsNum() < 1) {
        minic_log(LOG_ERROR, "取负操作的操作数不足");
        return;
    }

    Value * result = inst;
    Value * arg = getSafeOperand(inst, 0);
    
    if (!arg) {
        minic_log(LOG_ERROR, "取负操作的操作数为空");
        return;
    }

    // 分配寄存器
    int32_t arg_reg = simpleRegisterAllocator.Allocate(arg);
    int32_t result_reg = simpleRegisterAllocator.Allocate(result);

    // 加载操作数
    iloc.load_var(arg_reg, arg);

    // 执行取负操作 (rsb = reverse subtract)
    iloc.inst("rsb", 
              PlatformArm32::regName[result_reg], 
              PlatformArm32::regName[arg_reg], 
              "#0");

    // 存储结果
    iloc.store_var(result_reg, result, ARM32_TMP_REG_NO);

    // 释放寄存器
    simpleRegisterAllocator.free(arg_reg);
    simpleRegisterAllocator.free(result_reg);
}

/// @brief 安全获取操作数
Value* InstSelectorArm32::getSafeOperand(Instruction* inst, unsigned int index) {
    if (!inst) return nullptr;
    if (index >= inst->getOperandsNum()) return nullptr;
    return inst->getOperand(index);
}

// // 在类定义中添加计数器成员变量
// private:
//     int32_t realArgCount = 0;
//     int32_t argCount = 0; // 如果需要跟踪ARG指令的数量
