///*
// * canfd.c
// *
// *  Created on: Feb 17, 2021
// *      Author: mostafa
// */
//
///**
//  * @brief  Initializes the FDCAN peripheral according to the specified
//  *         parameters in the FDCAN_InitTypeDef structure.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan)
//{
//  uint32_t tickstart;
//
//  /* Check FDCAN handle */
//  if (hfdcan == NULL)
//  {
//    return HAL_ERROR;
//  }
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
//  if (hfdcan->Instance == FDCAN1)
//  {
//    assert_param(IS_FDCAN_CKDIV(hfdcan->Init.ClockDivider));
//  }
//
//  assert_param(IS_FDCAN_FRAME_FORMAT(hfdcan->Init.FrameFormat));
//  assert_param(IS_FDCAN_MODE(hfdcan->Init.Mode));
//  assert_param(IS_FUNCTIONAL_STATE(hfdcan->Init.AutoRetransmission));
//  assert_param(IS_FUNCTIONAL_STATE(hfdcan->Init.TransmitPause));
//  assert_param(IS_FUNCTIONAL_STATE(hfdcan->Init.ProtocolException));
//  assert_param(IS_FDCAN_NOMINAL_PRESCALER(hfdcan->Init.NominalPrescaler));
//  assert_param(IS_FDCAN_NOMINAL_SJW(hfdcan->Init.NominalSyncJumpWidth));
//  assert_param(IS_FDCAN_NOMINAL_TSEG1(hfdcan->Init.NominalTimeSeg1));
//  assert_param(IS_FDCAN_NOMINAL_TSEG2(hfdcan->Init.NominalTimeSeg2));
//
//  if (hfdcan->Init.FrameFormat == FDCAN_FRAME_FD_BRS)
//  {
//    assert_param(IS_FDCAN_DATA_PRESCALER(hfdcan->Init.DataPrescaler));
//    assert_param(IS_FDCAN_DATA_SJW(hfdcan->Init.DataSyncJumpWidth));
//    assert_param(IS_FDCAN_DATA_TSEG1(hfdcan->Init.DataTimeSeg1));
//    assert_param(IS_FDCAN_DATA_TSEG2(hfdcan->Init.DataTimeSeg2));
//  }
//  assert_param(IS_FDCAN_MAX_VALUE(hfdcan->Init.StdFiltersNbr, SRAMCAN_FLS_NBR));
//  assert_param(IS_FDCAN_MAX_VALUE(hfdcan->Init.ExtFiltersNbr, SRAMCAN_FLE_NBR));
//  assert_param(IS_FDCAN_TX_FIFO_QUEUE_MODE(hfdcan->Init.TxFifoQueueMode));
//
//
//#if 1
//  if (hfdcan->State == HAL_FDCAN_STATE_RESET)
//  {
//    /* Allocate lock resource and initialize it */
//    hfdcan->Lock = HAL_UNLOCKED;
//
//    /* Init the low level hardware: CLOCK, NVIC */
//   // HAL_FDCAN_MspInit(hfdcan);
//  }
//#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
//
//  /* Exit from Sleep mode */
//  CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_CSR);
//
//  /* Get tick */
//  tickstart = HAL_GetTick();
//
//  /* Check Sleep mode acknowledge  make sure that clock is working ok */
//  while ((hfdcan->Instance->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
//  {
//    if ((HAL_GetTick() - tickstart) > FDCAN_TIMEOUT_VALUE)
//    {
//      /* Update error code */
//      hfdcan->ErrorCode |= HAL_FDCAN_ERROR_TIMEOUT;
//
//      /* Change FDCAN state */
//      hfdcan->State = HAL_FDCAN_STATE_ERROR;
//
//      return HAL_ERROR;
//    }
//  }
//
//  /* Request initialisation */
//  SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_INIT);
//
//  /* Get tick */
//  tickstart = HAL_GetTick();
//
//  /* Wait until the INIT bit into CCCR register is set */
//  while ((hfdcan->Instance->CCCR & FDCAN_CCCR_INIT) == 0U)
//  {
//    /* Check for the Timeout */
//    if ((HAL_GetTick() - tickstart) > FDCAN_TIMEOUT_VALUE)
//    {
//      /* Update error code */
//      hfdcan->ErrorCode |= HAL_FDCAN_ERROR_TIMEOUT;
//
//      /* Change FDCAN state */
//      hfdcan->State = HAL_FDCAN_STATE_ERROR;
//
//      return HAL_ERROR;
//    }
//  }
//
//  /* Enable configuration change */
//  SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_CCE);
//
//  /* Check FDCAN instance */
//  if (hfdcan->Instance == FDCAN1)
//  {
//    /* Configure Clock divider */
//    FDCAN_CONFIG->CKDIV = hfdcan->Init.ClockDivider;
//  }
//
//  /* Set the no automatic retransmission */
//  if (hfdcan->Init.AutoRetransmission == ENABLE)
//  {
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_DAR);
//  }
//  else
//  {
//    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_DAR);
//  }
//
//  /* Set the transmit pause feature */
//  if (hfdcan->Init.TransmitPause == ENABLE)
//  {
//    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_TXP);
//  }
//  else
//  {
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_TXP);
//  }
//
//  /* Set the Protocol Exception Handling */
//  if (hfdcan->Init.ProtocolException == ENABLE)
//  {
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_PXHD);
//  }
//  else
//  {
//    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_PXHD);
//  }
//
//  /* Set FDCAN Frame Format */
//  MODIFY_REG(hfdcan->Instance->CCCR, FDCAN_FRAME_FD_BRS, hfdcan->Init.FrameFormat);
//
//  /* Reset FDCAN Operation Mode ,clear before you write */
//  CLEAR_BIT(hfdcan->Instance->CCCR, (FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM));
//  CLEAR_BIT(hfdcan->Instance->TEST, FDCAN_TEST_LBCK);
//
//  /* Set FDCAN Operating Mode:
//               | Normal | Restricted |    Bus     | Internal | External
//               |        | Operation  | Monitoring | LoopBack | LoopBack
//     CCCR.TEST |   0    |     0      |     0      |    1     |    1
//     CCCR.MON  |   0    |     0      |     1      |    1     |    0
//     TEST.LBCK |   0    |     0      |     0      |    1     |    1
//     CCCR.ASM  |   0    |     1      |     0      |    0     |    0
//  */
//  if (hfdcan->Init.Mode == FDCAN_MODE_RESTRICTED_OPERATION)
//  {
//    /* Enable Restricted Operation mode */
//    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_ASM);
//  }
//  else if (hfdcan->Init.Mode != FDCAN_MODE_NORMAL)
//  {
//    if (hfdcan->Init.Mode != FDCAN_MODE_BUS_MONITORING)
//    {
//      /* Enable write access to TEST register */
//      SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_TEST);
//
//      /* Enable LoopBack mode */
//      SET_BIT(hfdcan->Instance->TEST, FDCAN_TEST_LBCK);
//
//      if (hfdcan->Init.Mode == FDCAN_MODE_INTERNAL_LOOPBACK)
//      {
//        SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_MON);
//      }
//    }
//    else
//    {
//      /* Enable bus monitoring mode */
//      SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_MON);
//    }
//  }
//  else
//  {
//    /* Nothing to do: normal mode */
//  }
//
//  /* Set the nominal bit timing register */
//  hfdcan->Instance->NBTP = ((((uint32_t)hfdcan->Init.NominalSyncJumpWidth - 1U) << FDCAN_NBTP_NSJW_Pos) | \
//                            (((uint32_t)hfdcan->Init.NominalTimeSeg1 - 1U) << FDCAN_NBTP_NTSEG1_Pos)    | \
//                            (((uint32_t)hfdcan->Init.NominalTimeSeg2 - 1U) << FDCAN_NBTP_NTSEG2_Pos)    | \
//                            (((uint32_t)hfdcan->Init.NominalPrescaler - 1U) << FDCAN_NBTP_NBRP_Pos));
//
//  /* If FD operation with BRS is selected, set the data bit timing register */
//  if (hfdcan->Init.FrameFormat == FDCAN_FRAME_FD_BRS)
//  {
//    hfdcan->Instance->DBTP = ((((uint32_t)hfdcan->Init.DataSyncJumpWidth - 1U) << FDCAN_DBTP_DSJW_Pos)  | \
//                              (((uint32_t)hfdcan->Init.DataTimeSeg1 - 1U) << FDCAN_DBTP_DTSEG1_Pos)     | \
//                              (((uint32_t)hfdcan->Init.DataTimeSeg2 - 1U) << FDCAN_DBTP_DTSEG2_Pos)     | \
//                              (((uint32_t)hfdcan->Init.DataPrescaler - 1U) << FDCAN_DBTP_DBRP_Pos));
//  }
//
//  /* Select between Tx FIFO and Tx Queue operation modes */
//  SET_BIT(hfdcan->Instance->TXBC, hfdcan->Init.TxFifoQueueMode);
//
//  /* Calculate each RAM block address , register the ram address */
//  FDCAN_CalcultateRamBlockAddresses(hfdcan);
//
//  /* Initialize the Latest Tx request buffer index */
//  hfdcan->LatestTxFifoQRequest = 0U;
//
//  /* Initialize the error code */
//  hfdcan->ErrorCode = HAL_FDCAN_ERROR_NONE;
//
//  /* Initialize the FDCAN state */
//  hfdcan->State = HAL_FDCAN_STATE_READY;
//
//  /* Return function status */
//  return HAL_OK;
//}
//
//
/**
  * @brief  Calculate each RAM block start address and size
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @retval none
 */
//static void FDCAN_CalcultateRamBlockAddresses(FDCAN_HandleTypeDef *hfdcan)
//{
//  uint32_t RAMcounter;
//  uint32_t SramCanInstanceBase = SRAMCAN_BASE;
//#if defined(FDCAN2)
//
//  if (hfdcan->Instance == FDCAN2)
//  {
//    SramCanInstanceBase += SRAMCAN_SIZE;
//  }
//#endif /* FDCAN2 */
//#if defined(FDCAN3)
//  if (hfdcan->Instance == FDCAN3)
//  {
//    SramCanInstanceBase += SRAMCAN_SIZE * 2U;
//  }
//#endif /* FDCAN3 */
//
//  /* Standard filter list start address */
//  hfdcan->msgRam.StandardFilterSA = SramCanInstanceBase + SRAMCAN_FLSSA;
//
//  /* Standard filter elements number */
//  MODIFY_REG(hfdcan->Instance->RXGFC, FDCAN_RXGFC_LSS, (hfdcan->Init.StdFiltersNbr << FDCAN_RXGFC_LSS_Pos));
//
//  /* Extended filter list start address */
//  hfdcan->msgRam.ExtendedFilterSA = SramCanInstanceBase + SRAMCAN_FLESA;
//
//  /* Extended filter elements number */
//  MODIFY_REG(hfdcan->Instance->RXGFC, FDCAN_RXGFC_LSE, (hfdcan->Init.ExtFiltersNbr << FDCAN_RXGFC_LSE_Pos));
//
//  /* Rx FIFO 0 start address */
//  hfdcan->msgRam.RxFIFO0SA = SramCanInstanceBase + SRAMCAN_RF0SA;
//
//  /* Rx FIFO 1 start address */
//  hfdcan->msgRam.RxFIFO1SA = SramCanInstanceBase + SRAMCAN_RF1SA;
//
//  /* Tx event FIFO start address */
//  hfdcan->msgRam.TxEventFIFOSA = SramCanInstanceBase + SRAMCAN_TEFSA;
//
//  /* Tx FIFO/queue start address */
//  hfdcan->msgRam.TxFIFOQSA = SramCanInstanceBase + SRAMCAN_TFQSA;
//
//  /* Flush the allocated Message RAM area */
//  for (RAMcounter = SramCanInstanceBase; RAMcounter < (SramCanInstanceBase + SRAMCAN_SIZE); RAMcounter += 4U)
//  {
//    *(uint32_t *)(RAMcounter) = 0x00000000U;
//  }
//}

///**
//  * @brief  Configure the FDCAN global filter.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  NonMatchingStd Defines how received messages with 11-bit IDs that
//  *         do not match any element of the filter list are treated.
//  *         This parameter can be a value of @arg FDCAN_Non_Matching_Frames.
//  * @param  NonMatchingExt Defines how received messages with 29-bit IDs that
//  *         do not match any element of the filter list are treated.
//  *         This parameter can be a value of @arg FDCAN_Non_Matching_Frames.
//  * @param  RejectRemoteStd Filter or reject all the remote 11-bit IDs frames.
//  *         This parameter can be a value of @arg FDCAN_Reject_Remote_Frames.
//  * @param  RejectRemoteExt Filter or reject all the remote 29-bit IDs frames.
//  *         This parameter can be a value of @arg FDCAN_Reject_Remote_Frames.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_ConfigGlobalFilter(FDCAN_HandleTypeDef *hfdcan,uint32_t NonMatchingStd, uint32_t NonMatchingExt,uint32_t RejectRemoteStd,uint32_t RejectRemoteExt)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_NON_MATCHING(NonMatchingStd));
//  assert_param(IS_FDCAN_NON_MATCHING(NonMatchingExt));
//  assert_param(IS_FDCAN_REJECT_REMOTE(RejectRemoteStd));
//  assert_param(IS_FDCAN_REJECT_REMOTE(RejectRemoteExt));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Configure global filter */
//    MODIFY_REG(hfdcan->Instance->RXGFC, (FDCAN_RXGFC_ANFS |
//                                         FDCAN_RXGFC_ANFE |
//                                         FDCAN_RXGFC_RRFS |
//                                         FDCAN_RXGFC_RRFE),
//
//               ((NonMatchingStd << FDCAN_RXGFC_ANFS_Pos)  |
//                (NonMatchingExt << FDCAN_RXGFC_ANFE_Pos)  |
//                (RejectRemoteStd << FDCAN_RXGFC_RRFS_Pos) |
//                (RejectRemoteExt << FDCAN_RXGFC_RRFE_Pos)));
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Enable the timestamp counter.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  TimestampOperation Timestamp counter operation.
//  *         This parameter can be a value of @arg FDCAN_Timestamp.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_EnableTimestampCounter(FDCAN_HandleTypeDef *hfdcan, uint32_t TimestampOperation)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_TIMESTAMP(TimestampOperation));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Enable timestamp counter */
//    MODIFY_REG(hfdcan->Instance->TSCC, FDCAN_TSCC_TSS, TimestampOperation);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Disable the timestamp counter.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_DisableTimestampCounter(FDCAN_HandleTypeDef *hfdcan)
//{
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Disable timestamp counter */
//    CLEAR_BIT(hfdcan->Instance->TSCC, FDCAN_TSCC_TSS);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Configure the timestamp counter.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  TimestampPrescaler Timestamp Counter Prescaler.
//  *         This parameter can be a value of @arg FDCAN_Timestamp_Prescaler.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_ConfigTimestampCounter(FDCAN_HandleTypeDef *hfdcan, uint32_t TimestampPrescaler)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_TIMESTAMP_PRESCALER(TimestampPrescaler));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Configure prescaler */
//    MODIFY_REG(hfdcan->Instance->TSCC, FDCAN_TSCC_TCP, TimestampPrescaler);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Get the timestamp counter value.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval Timestamp counter value
//  * to use it in your app it must be connected with a math function to calculate the current tick relative to the zero
//  */
//uint16_t HAL_FDCAN_GetTimestampCounter(FDCAN_HandleTypeDef *hfdcan)
//{
//  return (uint16_t)(hfdcan->Instance->TSCV);
//}
///**
//  * @brief  Reset the timestamp counter to zero.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_ResetTimestampCounter(FDCAN_HandleTypeDef *hfdcan)
//{
//  if ((hfdcan->Instance->TSCC & FDCAN_TSCC_TSS) != FDCAN_TIMESTAMP_EXTERNAL)
//  {
//    /* Reset timestamp counter.
//       Actually any write operation to TSCV clears the counter */
//    CLEAR_REG(hfdcan->Instance->TSCV);
//  }
//  else
//  {
//    /* Update error code.
//       Unable to reset external counter */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_SUPPORTED;
//
//    return HAL_ERROR;
//  }
//
//  /* Return function status */
//  return HAL_OK;
//}
/**
  * @brief  Configure the transmitter delay compensation.
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  TdcOffset Transmitter Delay Compensation Offset.
  *         This parameter must be a number between 0x00 and 0x7F.
  * @param  TdcFilter Transmitter Delay Compensation Filter Window Length.
  *         This parameter must be a number between 0x00 and 0x7F.
  * @retval HAL status
  */
//HAL_StatusTypeDef HAL_FDCAN_ConfigTxDelayCompensation(FDCAN_HandleTypeDef *hfdcan, uint32_t TdcOffset,
//                                                      uint32_t TdcFilter)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_MAX_VALUE(TdcOffset, 0x7FU));
//  assert_param(IS_FDCAN_MAX_VALUE(TdcFilter, 0x7FU));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Configure TDC offset and filter window */
//    hfdcan->Instance->TDCR = ((TdcFilter << FDCAN_TDCR_TDCF_Pos) | (TdcOffset << FDCAN_TDCR_TDCO_Pos));
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Enable the transmitter delay compensation.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_EnableTxDelayCompensation(FDCAN_HandleTypeDef *hfdcan)
//{
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Enable transmitter delay compensation */
//    SET_BIT(hfdcan->Instance->DBTP, FDCAN_DBTP_TDC);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Enable ISO 11898-1 protocol mode.
//  *         CAN FD frame format is according to ISO 11898-1 standard.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_EnableISOMode(FDCAN_HandleTypeDef *hfdcan)
//{
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Disable Non ISO protocol mode */
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_NISO);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
//
///**
//  * @brief  Disable ISO 11898-1 protocol mode.
//  *         CAN FD frame format is according to Bosch CAN FD specification V1.0.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_DisableISOMode(FDCAN_HandleTypeDef *hfdcan)
//{
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Enable Non ISO protocol mode */
//    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_NISO);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Start the FDCAN module.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan)
//{
//  if (hfdcan->State == HAL_FDCAN_STATE_READY)
//  {
//    /* Change FDCAN peripheral state */
//    hfdcan->State = HAL_FDCAN_STATE_BUSY;
//
//    /* Request leave initialisation */
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_INIT);
//
//    /* Reset the FDCAN ErrorCode */
//    hfdcan->ErrorCode = HAL_FDCAN_ERROR_NONE;
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Copy Tx message to the message RAM.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  pTxHeader pointer to a FDCAN_TxHeaderTypeDef structure.
//  * @param  pTxData pointer to a buffer containing the payload of the Tx frame.
//  * @param  BufferIndex index of the buffer to be configured.
//  * @retval none
// */
//static void FDCAN_CopyMessageToRAM(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData,
//                                   uint32_t BufferIndex)
//{
//  uint32_t TxElementW1;
//  uint32_t TxElementW2;
//  uint32_t *TxAddress;
//  uint32_t ByteCounter;
//
//  /* Build first word of Tx header element */
//  if (pTxHeader->IdType == FDCAN_STANDARD_ID)
//  {
//    TxElementW1 = (pTxHeader->ErrorStateIndicator |
//                   FDCAN_STANDARD_ID |
//                   pTxHeader->TxFrameType |
//                   (pTxHeader->Identifier << 18U));
//  }
//  else /* pTxHeader->IdType == FDCAN_EXTENDED_ID */
//  {
//    TxElementW1 = (pTxHeader->ErrorStateIndicator |
//                   FDCAN_EXTENDED_ID |
//                   pTxHeader->TxFrameType |
//                   pTxHeader->Identifier);
//  }
//
//  /* Build second word of Tx header element */
//  TxElementW2 = ((pTxHeader->MessageMarker << 24U) |
//                 pTxHeader->TxEventFifoControl |
//                 pTxHeader->FDFormat |
//                 pTxHeader->BitRateSwitch |
//                 pTxHeader->DataLength);
//
//  /* Calculate Tx element address */
//  TxAddress = (uint32_t *)(hfdcan->msgRam.TxFIFOQSA + (BufferIndex * SRAMCAN_TFQ_SIZE));
//
//  /* Write Tx element header to the message RAM */
//  *TxAddress = TxElementW1;
//  TxAddress++;
//  *TxAddress = TxElementW2;
//  TxAddress++;
//
//  /* Write Tx payload to the message RAM ,what happens if we removed the 32typecasting*/
//  for (ByteCounter = 0; ByteCounter < DLCtoBytes[pTxHeader->DataLength >> 16U]; ByteCounter += 4U)
//  {
//    *TxAddress = (((uint32_t)pTxData[ByteCounter + 3U] << 24U) |
//                  ((uint32_t)pTxData[ByteCounter + 2U] << 16U) |
//                  ((uint32_t)pTxData[ByteCounter + 1U] << 8U)  |
//                  (uint32_t)pTxData[ByteCounter]);
//    TxAddress++;
//  }
//}
//HAL_StatusTypeDef HAL_FDCAN_AddMessageToTxFifoQ(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData)
//{
//  uint32_t PutIndex;
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_ID_TYPE(pTxHeader->IdType));
//  if (pTxHeader->IdType == FDCAN_STANDARD_ID)
//  {
//    assert_param(IS_FDCAN_MAX_VALUE(pTxHeader->Identifier, 0x7FFU));
//  }
//  else /* pTxHeader->IdType == FDCAN_EXTENDED_ID */
//  {
//    assert_param(IS_FDCAN_MAX_VALUE(pTxHeader->Identifier, 0x1FFFFFFFU));
//  }
//  assert_param(IS_FDCAN_FRAME_TYPE(pTxHeader->TxFrameType));
//  assert_param(IS_FDCAN_DLC(pTxHeader->DataLength));
//  assert_param(IS_FDCAN_ESI(pTxHeader->ErrorStateIndicator));
//  assert_param(IS_FDCAN_BRS(pTxHeader->BitRateSwitch));
//  assert_param(IS_FDCAN_FDF(pTxHeader->FDFormat));
//  assert_param(IS_FDCAN_EFC(pTxHeader->TxEventFifoControl));
//  assert_param(IS_FDCAN_MAX_VALUE(pTxHeader->MessageMarker, 0xFFU));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_BUSY)
//  {
//    /* Check that the Tx FIFO/Queue is not full */
//    if ((hfdcan->Instance->TXFQS & FDCAN_TXFQS_TFQF) != 0U)
//    {
//      /* Update error code */
//      hfdcan->ErrorCode |= HAL_FDCAN_ERROR_FIFO_FULL;
//
//      return HAL_ERROR;
//    }
//    else
//    {
//      /* Retrieve the Tx FIFO PutIndex */
//      PutIndex = ((hfdcan->Instance->TXFQS & FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_Pos);
//
//      /* Add the message to the Tx FIFO/Queue */
//      FDCAN_CopyMessageToRAM(hfdcan, pTxHeader, pTxData, PutIndex);
//
//      /* Activate the corresponding transmission request */
//      hfdcan->Instance->TXBAR = ((uint32_t)1 << PutIndex);
//
//      /* Store the Latest Tx FIFO/Queue Request Buffer Index ?? */
//      hfdcan->LatestTxFifoQRequest = ((uint32_t)1 << PutIndex);
//    }
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Abort transmission request
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  BufferIndex buffer index.
//  *         This parameter can be any combination of @arg FDCAN_Tx_location.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_TX_LOCATION_LIST(BufferIndex));
//
//  if (hfdcan->State == HAL_FDCAN_STATE_BUSY)
//  {
//    /* Add cancellation request */
//    hfdcan->Instance->TXBCR = BufferIndex;
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;
//
//    return HAL_ERROR;
//  }
//}
//
///**
//  * @brief  Get an FDCAN frame from the Rx FIFO zone into the message RAM.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  RxLocation Location of the received message to be read.
//  *         This parameter can be a value of @arg FDCAN_Rx_location.
//  * @param  pRxHeader pointer to a FDCAN_RxHeaderTypeDef structure.
//  * @param  pRxData pointer to a buffer where the payload of the Rx frame will be stored.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_GetRxMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t RxLocation,
//                                         FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData)
//{
//  uint32_t *RxAddress;
//  uint8_t  *pData;
//  uint32_t ByteCounter;
//  uint32_t GetIndex;
//  HAL_FDCAN_StateTypeDef state = hfdcan->State;
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_RX_FIFO(RxLocation));
//
//  if (state == HAL_FDCAN_STATE_BUSY)
//  {
//    if (RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
//    {
//      /* Check that the Rx FIFO 0 is not empty */
//      if ((hfdcan->Instance->RXF0S & FDCAN_RXF0S_F0FL) == 0U)
//      {
//        /* Update error code */
//        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_FIFO_EMPTY;
//
//        return HAL_ERROR;
//      }
//      else
//      {
//        /* Calculate Rx FIFO 0 element address */
//        GetIndex = ((hfdcan->Instance->RXF0S & FDCAN_RXF0S_F0GI) >> FDCAN_RXF0S_F0GI_Pos);
//        RxAddress = (uint32_t *)(hfdcan->msgRam.RxFIFO0SA + (GetIndex * SRAMCAN_RF0_SIZE));
//      }
//    }
//    else /* Rx element is assigned to the Rx FIFO 1 */
//    {
//      /* Check that the Rx FIFO 1 is not empty */
//      if ((hfdcan->Instance->RXF1S & FDCAN_RXF1S_F1FL) == 0U)
//      {
//        /* Update error code */
//        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_FIFO_EMPTY;
//
//        return HAL_ERROR;
//      }
//      else
//      {
//        /* Calculate Rx FIFO 1 element address */
//        GetIndex = ((hfdcan->Instance->RXF1S & FDCAN_RXF1S_F1GI) >> FDCAN_RXF1S_F1GI_Pos);
//        RxAddress = (uint32_t *)(hfdcan->msgRam.RxFIFO1SA + (GetIndex * SRAMCAN_RF1_SIZE));
//      }
//    }
//
//    /* Retrieve IdType */
//    pRxHeader->IdType = *RxAddress & FDCAN_ELEMENT_MASK_XTD;
//
//    /* Retrieve Identifier */
//    if (pRxHeader->IdType == FDCAN_STANDARD_ID) /* Standard ID element */
//    {
//      pRxHeader->Identifier = ((*RxAddress & FDCAN_ELEMENT_MASK_STDID) >> 18U);
//    }
//    else /* Extended ID element */
//    {
//      pRxHeader->Identifier = (*RxAddress & FDCAN_ELEMENT_MASK_EXTID);
//    }
//
//    /* Retrieve RxFrameType */
//    pRxHeader->RxFrameType = (*RxAddress & FDCAN_ELEMENT_MASK_RTR);
//
//    /* Retrieve ErrorStateIndicator */
//    pRxHeader->ErrorStateIndicator = (*RxAddress & FDCAN_ELEMENT_MASK_ESI);
//
//    /* Increment RxAddress pointer to second word of Rx FIFO element */
//    RxAddress++;
//
//    /* Retrieve RxTimestamp */
//    pRxHeader->RxTimestamp = (*RxAddress & FDCAN_ELEMENT_MASK_TS);
//
//    /* Retrieve DataLength */
//    pRxHeader->DataLength = (*RxAddress & FDCAN_ELEMENT_MASK_DLC);
//
//    /* Retrieve BitRateSwitch */
//    pRxHeader->BitRateSwitch = (*RxAddress & FDCAN_ELEMENT_MASK_BRS);
//
//    /* Retrieve FDFormat */
//    pRxHeader->FDFormat = (*RxAddress & FDCAN_ELEMENT_MASK_FDF);
//
//    /* Retrieve FilterIndex */
//    pRxHeader->FilterIndex = ((*RxAddress & FDCAN_ELEMENT_MASK_FIDX) >> 24U);
//
//    /* Retrieve NonMatchingFrame */
//    pRxHeader->IsFilterMatchingFrame = ((*RxAddress & FDCAN_ELEMENT_MASK_ANMF) >> 31U);
//
//    /* Increment RxAddress pointer to payload of Rx FIFO element */
//    RxAddress++;
//
//    /* Retrieve Rx payload */
//    pData = (uint8_t *)RxAddress;
//    for (ByteCounter = 0; ByteCounter < DLCtoBytes[pRxHeader->DataLength >> 16U]; ByteCounter++)
//    {
//      pRxData[ByteCounter] = pData[ByteCounter];
//    }
//
//    if (RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
//    {
//      /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the GetIndex */
//      hfdcan->Instance->RXF0A = GetIndex;
//    }
//    else /* Rx element is assigned to the Rx FIFO 1 */
//    {
//      /* Acknowledge the Rx FIFO 1 that the oldest element is read so that it increments the GetIndex */
//      hfdcan->Instance->RXF1A = GetIndex;
//    }
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Get an FDCAN Tx event from the Tx Event FIFO zone into the message RAM.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  pTxEvent pointer to a FDCAN_TxEventFifoTypeDef structure.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_GetTxEvent(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxEventFifoTypeDef *pTxEvent)
//{
//  uint32_t *TxEventAddress;
//  uint32_t GetIndex;
//  HAL_FDCAN_StateTypeDef state = hfdcan->State;
//
//  if (state == HAL_FDCAN_STATE_BUSY)
//  {
//    /* Check that the Tx event FIFO is not empty */
//    if ((hfdcan->Instance->TXEFS & FDCAN_TXEFS_EFFL) == 0U)
//    {
//      /* Update error code */
//      hfdcan->ErrorCode |= HAL_FDCAN_ERROR_FIFO_EMPTY;
//
//      return HAL_ERROR;
//    }
//
//    /* Calculate Tx event FIFO element address */
//    GetIndex = ((hfdcan->Instance->TXEFS & FDCAN_TXEFS_EFGI) >> FDCAN_TXEFS_EFGI_Pos);
//    TxEventAddress = (uint32_t *)(hfdcan->msgRam.TxEventFIFOSA + (GetIndex * SRAMCAN_TEF_SIZE));
//
//    /* Retrieve IdType */
//    pTxEvent->IdType = *TxEventAddress & FDCAN_ELEMENT_MASK_XTD;
//
//    /* Retrieve Identifier */
//    if (pTxEvent->IdType == FDCAN_STANDARD_ID) /* Standard ID element */
//    {
//      pTxEvent->Identifier = ((*TxEventAddress & FDCAN_ELEMENT_MASK_STDID) >> 18U);
//    }
//    else /* Extended ID element */
//    {
//      pTxEvent->Identifier = (*TxEventAddress & FDCAN_ELEMENT_MASK_EXTID);
//    }
//
//    /* Retrieve TxFrameType */
//    pTxEvent->TxFrameType = (*TxEventAddress & FDCAN_ELEMENT_MASK_RTR);
//
//    /* Retrieve ErrorStateIndicator */
//    pTxEvent->ErrorStateIndicator = (*TxEventAddress & FDCAN_ELEMENT_MASK_ESI);
//
//    /* Increment TxEventAddress pointer to second word of Tx Event FIFO element */
//    TxEventAddress++;
//
//    /* Retrieve TxTimestamp */
//    pTxEvent->TxTimestamp = (*TxEventAddress & FDCAN_ELEMENT_MASK_TS);
//
//    /* Retrieve DataLength */
//    pTxEvent->DataLength = (*TxEventAddress & FDCAN_ELEMENT_MASK_DLC);
//
//    /* Retrieve BitRateSwitch */
//    pTxEvent->BitRateSwitch = (*TxEventAddress & FDCAN_ELEMENT_MASK_BRS);
//
//    /* Retrieve FDFormat */
//    pTxEvent->FDFormat = (*TxEventAddress & FDCAN_ELEMENT_MASK_FDF);
//
//    /* Retrieve EventType */
//    pTxEvent->EventType = (*TxEventAddress & FDCAN_ELEMENT_MASK_ET);
//
//    /* Retrieve MessageMarker */
//    pTxEvent->MessageMarker = ((*TxEventAddress & FDCAN_ELEMENT_MASK_MM) >> 24U);
//
//    /* Acknowledge the Tx Event FIFO that the oldest element is read so that it increments the GetIndex */
//    hfdcan->Instance->TXEFA = GetIndex;
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Get protocol status.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  ProtocolStatus pointer to an FDCAN_ProtocolStatusTypeDef structure.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_GetProtocolStatus(FDCAN_HandleTypeDef *hfdcan, FDCAN_ProtocolStatusTypeDef *ProtocolStatus)
//{
//  uint32_t StatusReg;
//
//  /* Read the protocol status register */
//  StatusReg = READ_REG(hfdcan->Instance->PSR);
//
//  /* Fill the protocol status structure */
//  ProtocolStatus->LastErrorCode = (StatusReg & FDCAN_PSR_LEC);
//  ProtocolStatus->DataLastErrorCode = ((StatusReg & FDCAN_PSR_DLEC) >> FDCAN_PSR_DLEC_Pos);
//  ProtocolStatus->Activity = (StatusReg & FDCAN_PSR_ACT);
//  ProtocolStatus->ErrorPassive = ((StatusReg & FDCAN_PSR_EP) >> FDCAN_PSR_EP_Pos);
//  ProtocolStatus->Warning = ((StatusReg & FDCAN_PSR_EW) >> FDCAN_PSR_EW_Pos);
//  ProtocolStatus->BusOff = ((StatusReg & FDCAN_PSR_BO) >> FDCAN_PSR_BO_Pos);
//  ProtocolStatus->RxESIflag = ((StatusReg & FDCAN_PSR_RESI) >> FDCAN_PSR_RESI_Pos);
//  ProtocolStatus->RxBRSflag = ((StatusReg & FDCAN_PSR_RBRS) >> FDCAN_PSR_RBRS_Pos);
//  ProtocolStatus->RxFDFflag = ((StatusReg & FDCAN_PSR_REDL) >> FDCAN_PSR_REDL_Pos);
//  ProtocolStatus->ProtocolException = ((StatusReg & FDCAN_PSR_PXE) >> FDCAN_PSR_PXE_Pos);
//  ProtocolStatus->TDCvalue = ((StatusReg & FDCAN_PSR_TDCV) >> FDCAN_PSR_TDCV_Pos);
//
//  /* Return function status */
//  return HAL_OK;
//}
///**
//  * @brief  Check if a transmission request is pending on the selected Tx buffer.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  TxBufferIndex Tx buffer index.
//  *         This parameter can be any combination of @arg FDCAN_Tx_location.
//  * @retval Status
//  *          - 0 : No pending transmission request on TxBufferIndex list
//  *          - 1 : Pending transmission request on TxBufferIndex.
//  */
//uint32_t HAL_FDCAN_IsTxBufferMessagePending(FDCAN_HandleTypeDef *hfdcan, uint32_t TxBufferIndex)
//{
//  /* Check function parameters */
//  assert_param(IS_FDCAN_TX_LOCATION_LIST(TxBufferIndex));
//
//  /* Check pending transmission request on the selected buffer */
//  if ((hfdcan->Instance->TXBRP & TxBufferIndex) == 0U)
//  {
//    return 0;
//  }
//  return 1;
//}
///**
//  * @brief  Get error counter values.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  ErrorCounters pointer to an FDCAN_ErrorCountersTypeDef structure.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_GetErrorCounters(FDCAN_HandleTypeDef *hfdcan, FDCAN_ErrorCountersTypeDef *ErrorCounters)
//{
//  uint32_t CountersReg;
//
//  /* Read the error counters register */
//  CountersReg = READ_REG(hfdcan->Instance->ECR);
//
//  /* Fill the error counters structure */
//  ErrorCounters->TxErrorCnt = ((CountersReg & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
//  ErrorCounters->RxErrorCnt = ((CountersReg & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
//  ErrorCounters->RxErrorPassive = ((CountersReg & FDCAN_ECR_RP) >> FDCAN_ECR_RP_Pos);
//  ErrorCounters->ErrorLogging = ((CountersReg & FDCAN_ECR_CEL) >> FDCAN_ECR_CEL_Pos);
//
//  /* Return function status */
//  return HAL_OK;
//}
///**
//  * @brief  Return Rx FIFO fill level.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  RxFifo Rx FIFO.
//  *         This parameter can be one of the following values:
//  *           @arg FDCAN_RX_FIFO0: Rx FIFO 0
//  *           @arg FDCAN_RX_FIFO1: Rx FIFO 1
//  * @retval Rx FIFO fill level.
//  */
//uint32_t HAL_FDCAN_GetRxFifoFillLevel(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo)
//{
//  uint32_t FillLevel;
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_RX_FIFO(RxFifo));
//
//  if (RxFifo == FDCAN_RX_FIFO0)
//  {
//    FillLevel = hfdcan->Instance->RXF0S & FDCAN_RXF0S_F0FL;
//  }
//  else /* RxFifo == FDCAN_RX_FIFO1 */
//  {
//    FillLevel = hfdcan->Instance->RXF1S & FDCAN_RXF1S_F1FL;
//  }
//
//  /* Return Rx FIFO fill level */
//  return FillLevel;
//}
//
///**
//  * @brief  Return Tx FIFO free level: number of consecutive free Tx FIFO
//  *         elements starting from Tx FIFO GetIndex.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval Tx FIFO free level.
//  */
//uint32_t HAL_FDCAN_GetTxFifoFreeLevel(FDCAN_HandleTypeDef *hfdcan)
//{
//  uint32_t FreeLevel;
//
//  FreeLevel = hfdcan->Instance->TXFQS & FDCAN_TXFQS_TFFL;
//
//  /* Return Tx FIFO free level */
//  return FreeLevel;
//}
///**
//  * @brief  Check if the FDCAN peripheral entered Restricted Operation Mode.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval Status
//  *          - 0 : Normal FDCAN operation.
//  *          - 1 : Restricted Operation Mode active.
//  */
//uint32_t HAL_FDCAN_IsRestrictedOperationMode(FDCAN_HandleTypeDef *hfdcan)
//{
//  uint32_t OperationMode;
//
//  /* Get Operation Mode */
//  OperationMode = ((hfdcan->Instance->CCCR & FDCAN_CCCR_ASM) >> FDCAN_CCCR_ASM_Pos);
//
//  return OperationMode;
//}
//
///**
//  * @brief  Exit Restricted Operation Mode.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_ExitRestrictedOperationMode(FDCAN_HandleTypeDef *hfdcan)
//{
//  HAL_FDCAN_StateTypeDef state = hfdcan->State;
//
//  if ((state == HAL_FDCAN_STATE_READY) || (state == HAL_FDCAN_STATE_BUSY))
//  {
//    /* Exit Restricted Operation mode */
//    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_ASM);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_INITIALIZED;
//
//    return HAL_ERROR;
//  }
//}

///**
//  * @brief  Enable interrupts.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  ActiveITs indicates which interrupts will be enabled.
//  *         This parameter can be any combination of @arg FDCAN_Interrupts.
//  * @param  BufferIndexes Tx Buffer Indexes.
//  *         This parameter can be any combination of @arg FDCAN_Tx_location.
//  *         This parameter is ignored if ActiveITs does not include one of the following:
//  *           - FDCAN_IT_TX_COMPLETE
//  *           - FDCAN_IT_TX_ABORT_COMPLETE
//  * @retval HAL status
//  */
//HAL_StatusTypeDef HAL_FDCAN_ActivateNotification(FDCAN_HandleTypeDef *hfdcan, uint32_t ActiveITs,
//                                                 uint32_t BufferIndexes)
//{
//  HAL_FDCAN_StateTypeDef state = hfdcan->State;
//  uint32_t ITs_lines_selection;
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_IT(ActiveITs));
//  if ((ActiveITs & (FDCAN_IT_TX_COMPLETE | FDCAN_IT_TX_ABORT_COMPLETE)) != 0U)
//  {
//    assert_param(IS_FDCAN_TX_LOCATION_LIST(BufferIndexes));
//  }
//
//  if ((state == HAL_FDCAN_STATE_READY) || (state == HAL_FDCAN_STATE_BUSY))
//  {
////    SET_BIT(hfdcan->Instance->ILE, FDCAN_INTERRUPT_LINE0);
////    SET_BIT(hfdcan->Instance->ILE, FDCAN_INTERRUPT_LINE1);
//
//    if ((ActiveITs & FDCAN_IT_TX_COMPLETE) != 0U)
//    {
//      /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
//         but interrupt will only occur if TC is enabled in IE register */
//      SET_BIT(hfdcan->Instance->TXBTIE, BufferIndexes);
//    }
//
//    if ((ActiveITs & FDCAN_IT_TX_ABORT_COMPLETE) != 0U)
//    {
//      /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
//         but interrupt will only occur if TCF is enabled in IE register */
//      SET_BIT(hfdcan->Instance->TXBCIE, BufferIndexes);
//    }
//
//    /* Enable the selected interrupts */
//    __HAL_FDCAN_ENABLE_IT(hfdcan, ActiveITs);
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_INITIALIZED;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Assign interrupts to either Interrupt line 0 or 1.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  ITList indicates which interrupts group will be assigned to the selected interrupt line.
//  *         This parameter can be any combination of @arg FDCAN_Interrupts_Group.
//  * @param  InterruptLine Interrupt line.
//  *         This parameter can be a value of @arg FDCAN_Interrupt_Line.
//  * @retval HAL status
//  * whole group not single interrupt
//  */
//HAL_StatusTypeDef HAL_FDCAN_ConfigInterruptLines(FDCAN_HandleTypeDef *hfdcan, uint32_t ITList, uint32_t InterruptLine)
//{
//  HAL_FDCAN_StateTypeDef state = hfdcan->State;
//
//  /* Check function parameters */
//  assert_param(IS_FDCAN_IT_GROUP(ITList));
//  assert_param(IS_FDCAN_IT_LINE(InterruptLine));
//
//  if ((state == HAL_FDCAN_STATE_READY) || (state == HAL_FDCAN_STATE_BUSY))
//  {
//    /* Assign list of interrupts to the selected line */
//    if (InterruptLine == FDCAN_INTERRUPT_LINE0)
//    {
//      CLEAR_BIT(hfdcan->Instance->ILS, ITList);
//    }
//    else /* InterruptLine == FDCAN_INTERRUPT_LINE1 */
//    {
//      SET_BIT(hfdcan->Instance->ILS, ITList);
//    }
//
//    /* Return function status */
//    return HAL_OK;
//  }
//  else
//  {
//    /* Update error code */
//    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_INITIALIZED;
//
//    return HAL_ERROR;
//  }
//}
///**
//  * @brief  Handles FDCAN interrupt request.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval HAL status
//  */
//void HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *hfdcan)
//{
//  uint32_t TxEventFifoITs;
//  uint32_t RxFifo0ITs;
//  uint32_t RxFifo1ITs;
//  uint32_t Errors;
//  uint32_t ErrorStatusITs;
//  uint32_t TransmittedBuffers;
//  uint32_t AbortedBuffers;
//
//  /* The stm32 machines doesn't have separate interrupt register  so it read and mask to get the masked *******************************/
//  TxEventFifoITs = hfdcan->Instance->IR & FDCAN_TX_EVENT_FIFO_MASK;
//  TxEventFifoITs &= hfdcan->Instance->IE;
//
//  RxFifo0ITs = hfdcan->Instance->IR & FDCAN_RX_FIFO0_MASK;
//  RxFifo0ITs &= hfdcan->Instance->IE;
//
//  RxFifo1ITs = hfdcan->Instance->IR & FDCAN_RX_FIFO1_MASK;
//  RxFifo1ITs &= hfdcan->Instance->IE;
//
//  Errors = hfdcan->Instance->IR & FDCAN_ERROR_MASK;
//  Errors &= hfdcan->Instance->IE;
//
//  /* bus off warning passive error*/
//  ErrorStatusITs = hfdcan->Instance->IR & FDCAN_ERROR_STATUS_MASK;
//  ErrorStatusITs &= hfdcan->Instance->IE;
//
//  /* Transmission Complete interrupt management , mask the buffer index *******************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_COMPLETE) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_TX_COMPLETE) != 0U)
//    {
//      /* List of transmitted monitored buffers */
//      TransmittedBuffers = hfdcan->Instance->TXBTO;
//      TransmittedBuffers &= hfdcan->Instance->TXBTIE;
//
//      /* Clear the Transmission Complete flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_COMPLETE);
//
//      /* Transmission Complete Callback */
//      HAL_FDCAN_TxBufferCompleteCallback(hfdcan, TransmittedBuffers);
//    }
//  }
//  /* Transmission Abort interrupt management **********************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_ABORT_COMPLETE) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_TX_ABORT_COMPLETE) != 0U)
//    {
//      /* List of aborted monitored buffers */
//      AbortedBuffers = hfdcan->Instance->TXBCF;
//      AbortedBuffers &= hfdcan->Instance->TXBCIE;
//
//      /* Clear the Transmission Cancellation flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_ABORT_COMPLETE);
//
//      /* Transmission Cancellation Callback */
//      HAL_FDCAN_TxBufferAbortCallback(hfdcan, AbortedBuffers);
//    }
//  }
//  /* Tx event FIFO interrupts management **************************************/
//  if (TxEventFifoITs != 0U)
//  {
//    /* Clear the Tx Event FIFO flags */
//    __HAL_FDCAN_CLEAR_FLAG(hfdcan, TxEventFifoITs);
//    /* Tx Event FIFO Callback */
//    HAL_FDCAN_TxEventFifoCallback(hfdcan, TxEventFifoITs);
//  }
//  /* Rx FIFO 0 interrupts management ******************************************/
//  if (RxFifo0ITs != 0U)
//  {
//    /* Clear the Rx FIFO 0 flags */
//    __HAL_FDCAN_CLEAR_FLAG(hfdcan, RxFifo0ITs);
//    /* Rx FIFO 0 Callback */
//    HAL_FDCAN_RxFifo0Callback(hfdcan, RxFifo0ITs);
//  }
//  /* Rx FIFO 1 interrupts management ******************************************/
//  if (RxFifo1ITs != 0U)
//  {
//    /* Clear the Rx FIFO 1 flags */
//    __HAL_FDCAN_CLEAR_FLAG(hfdcan, RxFifo1ITs);
//    /* Rx FIFO 1 Callback */
//    HAL_FDCAN_RxFifo1Callback(hfdcan, RxFifo1ITs);
//  }
//  /* Tx FIFO empty interrupt management ***************************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_FIFO_EMPTY) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_TX_FIFO_EMPTY) != 0U)
//    {
//      /* Clear the Tx FIFO empty flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_FIFO_EMPTY);
//      /* Tx FIFO empty Callback */
//      HAL_FDCAN_TxFifoEmptyCallback(hfdcan);
//    }
//  }
//  /* Timestamp Wraparound interrupt management ********************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TIMESTAMP_WRAPAROUND) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_TIMESTAMP_WRAPAROUND) != 0U)
//    {
//      /* Clear the Timestamp Wraparound flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TIMESTAMP_WRAPAROUND);
//
//      /* Timestamp Wraparound Callback */
//      HAL_FDCAN_TimestampWraparoundCallback(hfdcan);
//    }
//  }
//  /* Timeout Occurred interrupt management ************************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TIMEOUT_OCCURRED) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_TIMEOUT_OCCURRED) != 0U)
//    {
//      /* Clear the Timeout Occurred flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TIMEOUT_OCCURRED);
//
//      /* Timeout Occurred Callback */
//      HAL_FDCAN_TimeoutOccurredCallback(hfdcan);
//    }
//  }
//  /* Error Status interrupts management ***************************************/
//  if (ErrorStatusITs != 0U)
//  {
//    /* Clear the Error flags */
//    __HAL_FDCAN_CLEAR_FLAG(hfdcan, ErrorStatusITs);
//
//    /* Error Status Callback */
//    HAL_FDCAN_ErrorStatusCallback(hfdcan, ErrorStatusITs);
//
//  }
//  /* Message RAM access failure interrupt management **************************/
//  if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_RAM_ACCESS_FAILURE) != 0U)
//  {
//    if (__HAL_FDCAN_GET_IT_SOURCE(hfdcan, FDCAN_IT_RAM_ACCESS_FAILURE) != 0U)
//    {
//      /* Clear the Message RAM access failure flag */
//      __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_RAM_ACCESS_FAILURE);
//
//      /* Update error code */
//      hfdcan->ErrorCode |= HAL_FDCAN_ERROR_RAM_ACCESS;
//      //HAL_FDCAN_ERROR_RAMACCESSCallback(hfdcan);
//    }
//  }
//  /* Error interrupts management **********************************************/
//  if (Errors != 0U)
//  {
//    /* Clear the Error flags */
//    __HAL_FDCAN_CLEAR_FLAG(hfdcan, Errors);
//
//    /* Update error code */
//    hfdcan->ErrorCode |= Errors;
//  }
//
//  if (hfdcan->ErrorCode != HAL_FDCAN_ERROR_NONE)
//  {
//    /* Error Callback */
//    HAL_FDCAN_ErrorCallback(hfdcan);
//  }
//}
///**
//  * @brief  Transmission Complete callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  BufferIndexes Indexes of the transmitted buffers.
//  *         This parameter can be any combination of @arg FDCAN_Tx_location.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(BufferIndexes);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TxBufferCompleteCallback could be implemented in the user file
//   */
//}
//__weak void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(BufferIndexes);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TxBufferAbortCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Tx Event callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  TxEventFifoITs indicates which Tx Event FIFO interrupts are signalled.
//  *         This parameter can be any combination of @arg FDCAN_Tx_Event_Fifo_Interrupts.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(TxEventFifoITs);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TxEventFifoCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Tx Event callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  TxEventFifoITs indicates which Tx Event FIFO interrupts are signalled.
//  *         This parameter can be any combination of @arg FDCAN_Tx_Event_Fifo_Interrupts.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(TxEventFifoITs);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TxEventFifoCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Rx FIFO 1 callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  RxFifo1ITs indicates which Rx FIFO 1 interrupts are signalled.
//  *         This parameter can be any combination of @arg FDCAN_Rx_Fifo1_Interrupts.
//  * @retval None
//  */
//__weak void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(RxFifo1ITs);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_RxFifo1Callback could be implemented in the user file
//   */
//}
//
///**
//  * @brief  Tx FIFO Empty callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TxFifoEmptyCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Timestamp Wraparound callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TimestampWraparoundCallback(FDCAN_HandleTypeDef *hfdcan)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TimestampWraparoundCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Timeout Occurred callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @retval None
//  */
//__weak void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *hfdcan)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_TimeoutOccurredCallback could be implemented in the user file
//   */
//}
///**
//  * @brief  Error status callback.
//  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
//  *         the configuration information for the specified FDCAN.
//  * @param  ErrorStatusITs indicates which Error Status interrupts are signaled.
//  *         This parameter can be any combination of @arg FDCAN_Error_Status_Interrupts.
//  * @retval None
//  */
//__weak void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//  UNUSED(ErrorStatusITs);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_ErrorStatusCallback could be implemented in the user file
//   */
//}
//__weak void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(hfdcan);
//
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_FDCAN_ErrorCallback could be implemented in the user file
//   */
//}
