/*
 * @Description:
 * @Author: lize
 * @Date: 2024-07-08
 * @LastEditors: lize
 */
// TODO: 不使用16字节的链表节点 而是使用64字节的节点，可以将缓存性能提高4倍？
// 理解为 将连续的4个节点数据合并为1个节点，这样数据就可以更好的利用缓存了。